<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 */
ini_set('include_path',ini_get('include_path').ZEND.':');
require_once 'Zend/Mail.php';
require_once 'Zend/Mail/Transport/Sendmail.php';
class PendingUser extends ActiveRecord
{
	private $id;
	private $email;
	private $password;
	private $date;

	/**
	 * This will load all fields in the table as properties of this class.
	 * You may want to replace this with, or add your own extra, custom loading
	 */
	public function __construct($id=null)
	{
		if ($id)
		{
			$PDO = Database::getConnection();
			if (ctype_digit($id))
			{
				$sql = 'select id,email,password,unix_timestamp(date) as date
						from pendingUsers where id=?';
			}
			elseif (strlen($id)==32)
			{
				$sql = 'select id,email,password,unix_timestamp(date) as date
						from pendingUsers where md5(concat(id,email,password))=?';
			}
			else
			{
				$sql = 'select id,email,password,unix_timestamp(date) as date
						from pendingUsers where email=?';
			}
			$query = $PDO->prepare($sql);
			$query->execute(array($id));

			$result = $query->fetchAll(PDO::FETCH_ASSOC);
			if (!count($result)) { throw new Exception('users/pending/unknownPendingAccount'); }
			foreach($result[0] as $field=>$value) { if ($value) $this->$field = $value; }
		}
		else
		{
			# This is where the code goes to generate a new, empty instance.
			# Set any default values for properties that need it here
			$this->date = time();
		}
	}

	/**
	 * This generates generic SQL that should work right away.
	 * You can replace this $fields code with your own custom SQL
	 * for each property of this class,
	 */
	public function save()
	{
		# Check for required fields here.  Throw an exception if anything is missing.
		if (!$this->email || strlen($this->password)!=32)
		{
			throw new Exception('missingRequiredFields');
		}

		# Make sure the email address isn't already an active user
		$PDO = Database::getConnection();
		$query = $PDO->prepare('select id from users where email=?');
		$query->execute(array($this->email));
		$result = $query->fetchAll();
		if (count($result)) { throw new Exception('users/userAlreadyExists'); }

		$fields = array();
		$fields['email'] = $this->email;
		$fields['password'] = $this->password;
		$fields['date'] = $this->date ? date('Y-m-d',$this->date) : null;

		# Split the fields up into a preparedFields array and a values array.
		# PDO->execute cannot take an associative array for values, so we have
		# to strip out the keys from $fields
		$preparedFields = array();
		foreach($fields as $key=>$value)
		{
			$preparedFields[] = "$key=?";
			$values[] = $value;
		}
		$preparedFields = implode(",",$preparedFields);


		if ($this->id) { $this->update($values,$preparedFields); }
		else { $this->insert($values,$preparedFields); }
	}

	private function update($values,$preparedFields)
	{
		$PDO = Database::getConnection();

		$sql = "update pendingUsers set $preparedFields where id={$this->id}";
		$query = $PDO->prepare($sql);
		$query->execute($values);
	}

	private function insert($values,$preparedFields)
	{
		$PDO = Database::getConnection();

		$sql = "insert pendingUsers set $preparedFields";
		$query = $PDO->prepare($sql);
		$query->execute($values);
		$this->id = $PDO->lastInsertID();
	}

	public function delete()
	{
		$PDO = Database::getConnection();

		$query = $PDO->prepare('delete from pendingUsers where id=?');
		$query->execute(array($this->id));
	}

	public function getHash()
	{
		return md5($this->id.$this->email.$this->password);
	}

	/**
	 * Turns this Pending Account into an actual User account
	 */
	public function activate()
	{
		$user = new User();
		$user->setAuthenticationMethod('local');
		$user->setUsername($this->email);
		$user->setEmail($this->email);
		$user->setPasswordHash($this->password);
		$user->save();

		$this->delete();

		return $user;
	}

	/**
	 * Sends an email to the user who requested the account.
	 * To activate the account, the user must respond with the hash
	 * contained in this email
	 */
	public function notify($message)
	{
		$mail = new Zend_Mail('utf-8');
		$mail->setBodyText($message);
		$mail->setFrom(ADMINISTRATOR_EMAIL, APPLICATION_NAME);
		$mail->addTo($this->getEmail());
		$mail->setSubject(APPLICATION_NAME.' account confirmation');
		$mail->send();
	}

	/**
	 * Generic Getters
	 */
	public function getId() { return $this->id; }
	public function getEmail() { return $this->email; }
	public function getDate($format=null)
	{
		if ($format && $this->date)
		{
			if (strpos($format,'%')!==false) { return strftime($format,$this->date); }
			else { return date($format,$this->date); }
		}
		else return $this->date;
	}

	/**
	 * Generic Setters
	 */
	public function setEmail($string) { $this->email = trim($string); }
	public function setPassword($string) { $this->password = md5(trim($string)); }
	public function setDate($date)
	{
		if (is_array($date)) { $this->date = $this->dateArrayToTimestamp($date); }
		elseif(ctype_digit($date)) { $this->date = $date; }
		else { $this->date = strtotime($date); }
	}
}
