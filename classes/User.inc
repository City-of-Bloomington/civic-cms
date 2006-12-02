<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
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


		private $department;
		private $roles;

		public function __construct($id = null)
		{
			global $PDO;

			if ($id)
			{
				# Load an existing user
				if (is_numeric($id)) { $sql = "select * from users where id=?"; }
				else { $sql = "select * from users where username=?"; }
				try
				{
					$query = $PDO->prepare($sql);
					$query->execute(array($id));
				}
				catch (Exception $e) { throw $e; }

				$result = $query->fetchAll();
				if (count($result[0]))
				{
					$user = $result[0];

					$this->id = $user['id'];
					$this->username = $user['username'];
					# Passwords are one-way encrypted.  They should not be loaded by default
					$this->authenticationMethod = $user['authenticationMethod'];

					$this->firstname = $user['firstname'];
					$this->lastname = $user['lastname'];
					$this->department_id = $user['department_id'];
					$this->email = $user['email'];
				}
				else { throw new Exception("unknownUser"); }
			}
		}

		public function save()
		{
			# Check for required fields before saving
			if (!$this->username || !$this->firstname || !$this->lastname) { throw new Exception("missingRequiredFields"); }

			$fields = array();
			$fields['username'] = $this->username;
			# Passwords should not be updated by default.  Use the savePassword() function
			$fields['firstname'] = $this->firstname ? $this->firstname : null;
			$fields['lastname'] = $this->lastname ? $this->lastname : null;
			$fields['authenticationMethod'] = $this->authenticationMethod ? $this->authenticationMethod : null;
			$fields['department_id'] = $this->department_id ? $this->department_id : null;
			$fields['email'] = $this->email ? $this->email : null;

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

			# Save the password only if they've typed one
			if ($this->getPassword()) { $this->savePassword(); }

			$this->updateRoles();
		}

		public function delete()
		{
			global $PDO;

			$PDO->beginTransaction();

			$sql = "delete from user_roles where user_id={$this->id}";
			if (false === $PDO->exec($sql)) { $e = $PDO->errorInfo(); $PDO->rollBack(); throw new Exception($sql.$e[2]); }

			$sql = "delete from users where id={$this->id}";
			if (false === $PDO->exec($sql)) { $e = $PDO->errorInfo(); $PDO->rollBack(); throw new Exception($sql.$e[2]); }

			$PDO->commit();
		}

		private function update($values,$preparedFields)
		{
			global $PDO;

			$sql = "update users set $preparedFields where id={$this->id}";
			if (false === $query = $PDO->prepare($sql)) { $e = $PDO->errorInfo(); throw new Exception($sql.$e[2]); }
			if (false === $query->execute($values)) { $e = $PDO->errorInfo(); throw new Exception($sql.$e[2]); }
		}

		private function insert($values,$preparedFields)
		{
			global $PDO;

			$sql = "insert users set $preparedFields";
			if (false === $query = $PDO->prepare($sql)) { $e = $PDO->errorInfo(); throw new Exception($sql.$e[2]); }
			if (false === $query->execute($values)) { $e = $PDO->errorInfo(); throw new Exception($sql.$e[2]); }
			$this->id = $PDO->lastInsertID();
		}


		private function updateRoles()
		{
			global $PDO;

			$roles = $this->getRoles();

			$sql = "delete from user_roles where user_id={$this->id}";
			if (false === $PDO->exec($sql)) { $e = $PDO->errorInfo(); throw new Exception($sql.$e[2]); }

			$statement = $PDO->prepare("insert user_roles set user_id={$this->id},role_id=?");
			foreach($roles as $role_id=>$role)
			{
				if (false === $statement->execute(array("$role_id"))) { $e = $PDO->errorInfo(); throw new Exception($sql.$e[2]); }
			}
		}

		protected function saveLocalPassword()
		{
			global $PDO;

			$sql = "update users set password=md5('{$this->password}') where id={$this->id}";
			if (false === $PDO->exec($sql)) { $e = $PDO->errorInfo(); throw new Exception($sql.$e[2]); }
		}

		protected function authenticateDatabase($password)
		{
			global $PDO;

			$sql = "select id from users where username='{$this->username}' and password=md5('$password')";
			$result = $PDO->query($sql);
			if ($user = $result->fetch()) { return true; }
			else { return false; }
			$result->closeCursor();
		}

		/* Takes a string or an array of strings and checks if the user has that role */
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
		 * In this system, users can only edit stuff if they're in the same department
		 * as the thing they're trying to edit
		 */
		public function canEdit($object)
		{
			return $this->department_id == $object->getDepartment_id();
		}

		/**
		 * Checks if the user has a watch on a document
		 */
		public function hasWatch($document)
		{
			global $PDO;

			$query = $PDO->prepare("select count(*) as watches from document_watches where document_id=? and user_id=?");
			$query->execute(array($document->getId(),$_SESSION['USER']->getId()));
			$result = $query->fetchAll();
			if ($result[0]['watches']) { return true; }
			else { return false; }
		}

		public function getId() { return $this->id; }
		public function getUsername() { return $this->username; }
		public function getPassword() { return $this->password; }
		public function getAuthenticationMethod() { return $this->authenticationMethod; }
		public function getFirstname() { return $this->firstname; }
		public function getLastname() { return $this->lastname; }
		public function getEmail() { return $this->email; }
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
			global $PDO;

			if (!$this->roles)
			{
				$this->roles = array();
				$sql = "select role_id,role from user_roles left join roles on role_id=id where user_id={$this->id}";
				if ($result = $PDO->query($sql))
				{
					foreach($result as $row) { $this->roles[$row['role_id']] = $row['role']; }
					$result->closeCursor();
				}
			}
			return $this->roles;
		}

		public function setUsername($string) { $this->username = trim($string); }
		public function setPassword($string) { if ($string) { $this->password = $string; } }
		public function setAuthenticationMethod($string) { $this->authenticationMethod = $string; }
		public function setFirstname($string) { $this->firstname = trim($string); }
		public function setLastname($string) { $this->lastname = trim($string); }
		public function setEmail($string) { $this->email = trim($string); }
		public function setDepartment_id($int) { $this->department = new Department($int); $this->department_id = $int; }
		public function setDepartment($department) { $this->department_id = $department->getId(); $this->department = $department; }
		/* Takes an array of role names.  Needs to look up the role_id and add them to the user */
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
?>