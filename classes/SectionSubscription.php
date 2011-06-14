<?php
/**
 * @copyright Copyright (C) 2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 */
ini_set('include_path',ini_get('include_path').ZEND.':');
require_once 'Zend/Mail.php';
require_once 'Zend/Mail/Transport/Sendmail.php';
class SectionSubscription extends ActiveRecord
{
	private $id;
	private $section_id;
	private $user_id;

	private $section;
	private $user;

	/**
	 * This will load all fields in the table as properties of this class.
	 * You may want to replace this with, or add your own extra, custom loading
	 */
	public function __construct($id=null)
	{
		if ($id)
		{
			$PDO = Database::getConnection();
			$query = $PDO->prepare('select * from section_subscriptions where id=?');
			$query->execute(array($id));

			$result = $query->fetchAll(PDO::FETCH_ASSOC);
			if (!count($result)) { throw new Exception('section_subscriptions/unknownSectionSubscription'); }
			foreach($result[0] as $field=>$value) { if ($value) $this->$field = $value; }
		}
		else
		{
			# This is where the code goes to generate a new, empty instance.
			# Set any default values for properties that need it here
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
		if (!$this->section_id || !$this->user_id) { throw new Exception('missingRequiredFields'); }

		$fields = array();
		$fields['section_id'] = $this->section_id;
		$fields['user_id'] = $this->user_id;

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

		$sql = "update section_subscriptions set $preparedFields where id={$this->id}";
		$query = $PDO->prepare($sql);
		$query->execute($values);
	}

	private function insert($values,$preparedFields)
	{
		$PDO = Database::getConnection();

		$sql = "insert section_subscriptions set $preparedFields";
		$query = $PDO->prepare($sql);
		$query->execute($values);
		$this->id = $PDO->lastInsertID();
	}

	public function delete()
	{
		$PDO = Database::getConnection();

		$query = $PDO->prepare('delete from section_subscriptions where id=?');
		$query->execute(array($this->id));
	}

	public function notify($message)
	{
		$mail = new Zend_Mail('utf-8');
		$mail->setBodyText($message);
		$mail->setFrom(ADMINISTRATOR_EMAIL, APPLICATION_NAME);
		$mail->addTo($this->getUser()->getEmail());
		$mail->setSubject($this->getSection()->getName().' subscription');
		$mail->send();
	}

	/**
	 * Generic Getters
	 */
	public function getId() { return $this->id; }
	public function getSection_id() { return $this->section_id; }
	public function getUser_id() { return $this->user_id; }

	public function getSection()
	{
		if ($this->section_id)
		{
			if (!$this->section) { $this->section = new Section($this->section_id); }
			return $this->section;
		}
		else return null;
	}

	public function getUser()
	{
		if ($this->user_id)
		{
			if (!$this->user) { $this->user = new User($this->user_id); }
			return $this->user;
		}
		else return null;
	}

	/**
	 * Generic Setters
	 */
	public function setSection_id($int) { $this->section = new Section($int); $this->section_id = $int; }
	public function setUser_id($int) { $this->user = new User($int); $this->user_id = $int; }

	public function setSection($section) { $this->section_id = $section->getId(); $this->section = $section; }
	public function setUser($user) { $this->user_id = $user->getId(); $this->user = $user; }
}
