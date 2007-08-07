<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
	class Department extends ActiveRecord
	{
		private $id;
		private $name;
		private $address1;
		private $address2;
		private $city;
		private $state;
		private $zip;
		private $phone;
		private $email;

		/**
		 * This will load all fields in the table as properties of this class.
		 * You may want to replace this with, or add your own extra, custom loading
		 */
		public function __construct($id=null)
		{
			global $PDO;

			if ($id)
			{
				$sql = "select * from departments where id=?";
				try
				{
					$query = $PDO->prepare($sql);
					$query->execute(array($id));
				}
				catch (Exception $e) { throw $e; }

				$result = $query->fetchAll();
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

			$fields = array();
			$fields['name'] = $this->name ? $this->name : null;
			$fields['address1'] = $this->address1 ? $this->address1 : null;
			$fields['address2'] = $this->address2 ? $this->address2 : null;
			$fields['city'] = $this->city ? $this->city : null;
			$fields['state'] = $this->state ? $this->state : null;
			$fields['zip'] = $this->zip ? $this->zip : null;
			$fields['phone'] = $this->phone ? $this->phone : null;
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


			if ($this->id) { $this->update($values,$preparedFields); }
			else { $this->insert($values,$preparedFields); }
		}

		private function update($values,$preparedFields)
		{
			global $PDO;

			$sql = "update departments set $preparedFields where id={$this->id}";
			if (false === $query = $PDO->prepare($sql)) { $e = $PDO->errorInfo(); throw new Exception($sql.$e[2]); }
			if (false === $query->execute($values)) { $e = $PDO->errorInfo(); throw new Exception($sql.$e[2]); }
		}

		private function insert($values,$preparedFields)
		{
			global $PDO;

			$sql = "insert departments set $preparedFields";
			if (false === $query = $PDO->prepare($sql)) { $e = $PDO->errorInfo(); throw new Exception($sql.$e[2]); }
			if (false === $query->execute($values)) { $e = $PDO->errorInfo(); throw new Exception($sql.$e[2]); }
			$this->id = $PDO->lastInsertID();
		}

		public function getUsers() { return new UserList(array('department_id'=>$this->id)); }

		public function __toString() { return $this->name; }

		public function getId() { return $this->id; }
		public function getName() { return $this->name; }
		public function getAddress1() { return $this->address1; }
		public function getAddress2() { return $this->address2; }
		public function getCity() { return $this->city; }
		public function getState() { return $this->state; }
		public function getZip() { return $this->zip; }
		public function getPhone() { return $this->phone; }
		public function getEmail() { return $this->email; }


		public function setName($string) { $this->name = trim($string); }
		public function setAddress1($string) { $this->address1 = trim($string); }
		public function setAddress2($string) { $this->address2 = trim($string); }
		public function setCity($string) { $this->city = trim($string); }
		public function setState($string) { $this->state = trim($string); }
		public function setZip($string) { $this->zip = trim($string); }
		public function setPhone($string) { $this->phone = trim($string); }
		public function setEmail($string) { $this->email = trim($string); }
	}
?>