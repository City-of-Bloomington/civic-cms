<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
	class Location extends ActiveRecord
	{
		private $id;
		private $name;
		private $locationType_id;
		private $address;
		private $description;
		private $directions;
		private $latitude;
		private $longitude;
		private $department_id;

		private $locationType;
		private $department;
		private $groups = array();

		/**
		 * This will load all fields in the table as properties of this class.
		 * You may want to replace this with, or add your own extra, custom loading
		 */
		public function __construct($id=null)
		{
			global $PDO;

			if ($id)
			{
				$sql = "select * from locations where id=?";
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
				$this->locationType_id = 1;
				$this->department_id = $_SESSION['USER']->getDepartmentid();
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
			if (!$this->name) { throw new Exception('missingName'); }
			if (!$this->description) { throw new Exception('missingDescription'); }
			if (!$this->address) { throw new Exception('locations/missingAddress'); }


			$fields = array();
			$fields['name'] = $this->name ? $this->name : null;
			$fields['locationType_id'] = $this->locationType_id ? $this->locationType_id : 1;
			$fields['address'] = $this->address ? $this->address : null;
			$fields['description'] = $this->description ? $this->description : null;
			$fields['directions'] = $this->directions ? $this->directions : null;
			$fields['latitude'] = $this->latitude ? $this->latitude : null;
			$fields['longitude'] = $this->longitude ? $this->longitude : null;
			$fields['department_id'] = $this->department_id;

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

			$this->saveLocationGroups();
		}

		private function update($values,$preparedFields)
		{
			global $PDO;

			$sql = "update locations set $preparedFields where id={$this->id}";
			if (false === $query = $PDO->prepare($sql)) { $e = $PDO->errorInfo(); throw new Exception($sql.$e[2]); }
			if (false === $query->execute($values)) { $e = $PDO->errorInfo(); throw new Exception($sql.$e[2]); }
		}

		private function insert($values,$preparedFields)
		{
			global $PDO;

			$sql = "insert locations set $preparedFields";
			if (false === $query = $PDO->prepare($sql)) { $e = $PDO->errorInfo(); throw new Exception($sql.$e[2]); }
			if (false === $query->execute($values)) { $e = $PDO->errorInfo(); throw new Exception($sql.$e[2]); }
			$this->id = $PDO->lastInsertID();
		}

		public function getLocationGroups()
		{
			if ($this->id)
			{
				if (!count($this->groups))
				{
					$list = new LocationGroupList(array('location_id'=>$this->id));
					foreach($list as $group) { $this->groups[$group->getId()] = $group; }
				}
			}
			return $this->groups;
		}
		public function hasGroup($group)
		{
			$id = is_int($group) ? $group : $group->getId();
			return in_array($id,array_keys($this->getLocationGroups()));
		}
		public function setLocationGroups(array $group_ids)
		{
			$this->groups = array();
			foreach($group_ids as $id)
			{
				$this->groups[$id] = new LocationGroup($id);
			}
		}
		private function saveLocationGroups()
		{
			global $PDO;

			$sql = "delete from locationGroup_locations where location_id={$this->id}";
			if (false === $PDO->exec($sql)) { $e = $PDO->errorInfo(); throw new Exception($sql.$e[2]); }

			$query = $PDO->prepare('insert locationGroup_locations values(?,?)');
			foreach($this->groups as $id=>$group)
			{
				$query->execute(array($id,$this->id));
			}
		}

		public function permitsEditingBy($user)
		{
			if ($user->hasRole(array('Administrator','Webmaster','Publisher'))) { return true; }
			if ($user->hasRole('Content Creator') && $user->getDepartment_id()==$this->department_id) { return true; }
			return false;
		}

		public function __toString() { return $this->name; }
		public function getType() { return $this->getLocationType()->getType(); }

		/**
		 * Generic Getters
		 */
		public function getId() { return $this->id; }
		public function getName() { return $this->name; }
		public function getLocationType_id() { return $this->locationType_id; }
		public function getAddress() { return $this->address; }
		public function getDescription() { return $this->description; }
		public function getDirections() { return $this->directions; }
		public function getLatitude() { return $this->latitude; }
		public function getLongitude() { return $this->longitude; }
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
		public function getLocationType()
		{
			if ($this->locationType_id)
			{
				if (!$this->locationType) { $this->locationType = new LocationType($this->locationType_id); }
				return $this->locationType;
			}
			else return null;
		}

		/**
		 * Generic Setters
		 */
		public function setName($string) { $this->name = trim($string); }
		public function setLocationType_id($int) { $this->locationType = new LocationType($int); $this->locationType_id = $int; }
		public function setAddress($string) { $this->address = trim($string); }
		public function setDescription($string) { $this->description = trim($string); }
		public function setDirections($text) { $this->directions = $text; }
		public function setLatitude($float) { $this->latitude = ereg_replace("[^0-9.\-]","",$float); }
		public function setLongitude($float) { $this->longitude = ereg_replace("[^0-9.\-]","",$float); }
		public function setDepartment_id($int) { $this->department = new Department($int); $this->department_id = $int; }

		public function setDepartment($department) { $this->department_id = $department->getId(); $this->department = $department; }
		public function setLocationType($locationType) { $this->locationType_id = $locationType->getId(); $this->locationType = $locationType; }
	}
?>