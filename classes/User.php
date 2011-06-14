<?php
/**
 * @copyright Copyright (C) 2006,2007,2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 */
class User extends SystemUser
{
	private $id;
	private $username;
	private $password;
	private $authenticationMethod;

	private $firstname;
	private $lastname;
	private $department_id;
	private $email;
	private $access = 'private';


	private $department;
	private $roles;

	private $newPassword; # The user's unencrypted password

	public function __construct($id = null)
	{
		if ($id)
		{
			$PDO = Database::getConnection();

			if (is_numeric($id)) { $sql = 'select * from users where id=?'; }
			else { $sql = 'select * from users where username=?'; }

			$query = $PDO->prepare($sql);
			$query->execute(array($id));

			$result = $query->fetchAll(PDO::FETCH_ASSOC);
			if (!count($result)) { throw new Exception('users/unknownUser'); }
			foreach($result[0] as $field=>$value) { if ($value) $this->$field = $value; }
		}
		else
		{
			# This is where the code goes to generate a new, empty instance.
			# Set any default values for properties that need it here
		}
	}

	public function save()
	{
		# Check for required fields before saving
		if (!$this->username || !$this->email) { throw new Exception("missingRequiredFields"); }

		$fields = array();
		$fields['username'] = $this->username;
		$fields['password'] = $this->password ? $this->password : null;
		$fields['firstname'] = $this->firstname ? $this->firstname : null;
		$fields['lastname'] = $this->lastname ? $this->lastname : null;
		$fields['authenticationMethod'] = $this->authenticationMethod ? $this->authenticationMethod : null;
		$fields['department_id'] = $this->department_id ? $this->department_id : null;
		$fields['email'] = $this->email;
		$fields['access'] = $this->access;

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

		# Do the database calls
		if ($this->id) { $this->update($values,$preparedFields); }
		else { $this->insert($values,$preparedFields); }

		# Save the password only if it's changed
		if ($this->passwordHasChanged()) { $this->savePassword(); }

		$this->updateRoles();
	}

	public function delete()
	{
		$PDO = Database::getConnection();
		$PDO->beginTransaction();

		try
		{
			$query = $PDO->prepare('delete from user_roles where user_id=?');
			$query->execute(array($this->id));

			$query = $PDO->prepare('delete from users where id=?');
			$query->execute(array($this->id));

			$PDO->commit();
		}
		catch(Exception $e)
		{
			$PDO->rollBack();
			throw $e;
		}
	}

	private function update($values,$preparedFields)
	{
		$PDO = Database::getConnection();

		$sql = "update users set $preparedFields where id={$this->id}";
		$query = $PDO->prepare($sql);
		$query->execute($values);
	}

	private function insert($values,$preparedFields)
	{
		$PDO = Database::getConnection();

		$sql = "insert users set $preparedFields";
		$query = $PDO->prepare($sql);
		$query->execute($values);
		$this->id = $PDO->lastInsertID();
	}


	private function updateRoles()
	{
		$PDO = Database::getConnection();

		$roles = $this->getRoles();

		$query = $PDO->prepare('delete from user_roles where user_id=?');
		$query->execute(array($this->id));

		$statement = $PDO->prepare("insert user_roles set user_id={$this->id},role_id=?");
		$query = $PDO->prepare('insert user_roles set user_id=?,role_id=?');
		foreach($roles as $role_id=>$role)
		{
			$query->execute(array($this->id,$role_id));
		}
	}

	/**
	 * Since passwords can be stored externally, we only want to bother trying
	 * to save them when they've actually changed
	 */
	public function passwordHasChanged() { return $this->newPassword ? true : false; }

	/**
	 * Callback function from the SystemUser class
	 * The SystemUser will determine where the password should be stored.
	 * If the password is stored locally, it will call this function
	 */
	protected function saveLocalPassword()
	{
		$PDO = Database::getConnection();

		# Passwords in the class should already be MD5 hashed
		$query = $PDO->prepare('update users set password=? where id=?');
		$query->execute(array($this->password,$this->id));
	}

	/**
	 * Callback function from the SystemUser class
	 * The SystemUser class will determine where the authentication
	 * should occur.  If the user should be authenticated locally,
	 * this function will be called.
	 */
	protected function authenticateDatabase($password)
	{
		$PDO = Database::getConnection();

		$query = $PDO->prepare('select id from users where username=? and password=md5(?)');
		$query->execute(array($this->username,$password));
		$result = $query->fetchAll();
		return count($result) ? true : false;
	}

	/**
	 * Takes a string or an array of strings and checks if the user has that role
	 */
	public function hasRole($roles)
	{
		if (is_array($roles))
		{
			foreach($roles as $role) { if (in_array($role,$this->getRoles())) { return true; } }
			return false;
		}
		else { return in_array($roles,$this->getRoles()); }
	}

	/**
	 * Checks if the user has a watch on a document
	 * @param Document $document
	 */
	public function hasWatch($document)
	{
		$PDO = Database::getConnection();

		$query = $PDO->prepare("select count(*) as watches from document_watches where document_id=? and user_id=?");
		$query->execute(array($document->getId(),$this->id));
		$result = $query->fetchAll();
		if ($result[0]['watches']) { return true; }
		else { return false; }
	}

	public function getSubscriptions()
	{
		return new SectionSubscriptionList(array('user_id'=>$this->id));
	}
	public function hasSubscription(Section $section)
	{
		$list = new SectionSubscriptionList(array('user_id'=>$this->id,'section_id'=>$section->getId()));
		return count($list) ? true : false;
	}
	/**
	 * Takes an array of section-ids and subscribes the user to all of them
	 * @param array $sectionIds
	 */
	public function setSubscriptions(array $sectionIds)
	{
		if ($this->id)
		{
			$PDO = Database::getConnection();
			$query = $PDO->prepare('delete from section_subscriptions where user_id=?');
			$query->execute(array($this->id));

			foreach($sectionIds as $id)
			{
				$subscription = new SectionSubscription();
				$subscription->setSection_id($id);
				$subscription->setUser($this);
				$subscription->save();
			}
		}
	}

	/**
	 * Generates an MD5 hash that can uniquely identify this user
	 */
	public function getHash()
	{
		return md5($this->id.$this->username.$this->email);
	}

	/**
	 * Getters
	 */
	public function getId() { return $this->id; }
	public function getUsername() { return $this->username; }
	public function getAuthenticationMethod() { return $this->authenticationMethod; }
	public function getFirstname() { return $this->firstname; }
	public function getLastname() { return $this->lastname; }
	public function getEmail() { return $this->email; }
	public function getAccess() { return $this->access; }
	public function getDepartment_id() { return $this->department_id; }
	public function getDepartment()
	{
		if ($this->department_id)
		{
			if (!$this->department) { $this->department = new Department($this->department_id); }
			return $this->department;
		}
		else return null;
	}
	public function getRoles()
	{
		if (!$this->roles)
		{
			$PDO = Database::getConnection();

			$sql = 'select role_id,role from user_roles left join roles on role_id=id where user_id=?';
			$query = $PDO->prepare($sql);
			$query->execute(array($this->id));
			$result = $query->fetchAll();

			$this->roles = array();
			foreach($result as $row) { $this->roles[$row['role_id']] = $row['role']; }
		}
		return $this->roles;
	}

	/**
	 * Setters
	 */
	public function setUsername($string) { $this->username = trim($string); }
	public function setAuthenticationMethod($string) { $this->authenticationMethod = trim($string); }
	public function setFirstname($string) { $this->firstname = trim($string); }
	public function setLastname($string) { $this->lastname = trim($string); }
	public function setEmail($string) { $this->email = trim($string); }
	public function setAccess($string) { $this->access = $string==='public' ? 'public' : 'private'; }
	public function setDepartment_id($int) { $this->department = new Department($int); $this->department_id = $int; }
	public function setDepartment($department) { $this->department_id = $department->getId(); $this->department = $department; }

	/**
	 * Takes a user-given password and converts it to an MD5 Hash
	 * @param String $string
	 */
	public function setPassword($string)
	{
		# Save the user given password, so we can update it externally, if needed
		$this->newPassword = trim($string);
		$this->password = md5(trim($string));
	}

	/**
	 * Takes a pre-existing MD5 hash
	 * @param MD5 $hash
	 */
	public function setPasswordHash($hash) { $this->password = trim($hash); }

	/**
	 * Takes an array of role names.  Loads the Roles from the database
	 * @param array $roleNames An array of names
	 */
	public function setRoles($array)
	{
		$this->roles = array();
		foreach($array as $id)
		{
			$role = new Role($id);
			$this->roles[$role->getId()] = $role->getRole();
		}
	}
}
