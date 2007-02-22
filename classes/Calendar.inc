<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
	class Calendar extends ActiveRecord
	{
		private $id;
		private $name;
		private $department_id;
		private $user_id;

		private $department;
		private $user;

		private $eventArray = array();

		/**
		 * This will load all fields in the table as properties of this class.
		 * You may want to replace this with, or add your own extra, custom loading
		 */
		public function __construct($id=null)
		{
			global $PDO;

			if ($id)
			{
				$sql = "select * from calendars where id=?";
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
			$fields['department_id'] = $this->department_id ? $this->department_id : null;
			$fields['user_id'] = $this->user_id ? $this->user_id : $_SESSION['USER']->getId();

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

			$sql = "update calendars set $preparedFields where id={$this->id}";
			if (false === $query = $PDO->prepare($sql)) { $e = $PDO->errorInfo(); throw new Exception($sql.$e[2]); }
			if (false === $query->execute($values)) { $e = $PDO->errorInfo(); throw new Exception($sql.$e[2]); }
		}

		private function insert($values,$preparedFields)
		{
			global $PDO;

			$sql = "insert calendars set $preparedFields";
			if (false === $query = $PDO->prepare($sql)) { $e = $PDO->errorInfo(); throw new Exception($sql.$e[2]); }
			if (false === $query->execute($values)) { $e = $PDO->errorInfo(); throw new Exception($sql.$e[2]); }
			$this->id = $PDO->lastInsertID();
		}

		private function fold($string) { return trim(preg_replace("/(.{1,72})/i","\\1\r\n ",trim($string))); }


		/**
		 * Generic Getters
		 */
		public function getId() { return $this->id; }
		public function getName() { return $this->name; }
		public function getDepartment_id() { return $this->department_id; }
		public function getUser_id() { return $this->user_id; }
		public function getDepartment()
		{
			if ($this->department_id)
			{
				if (!$this->department) { $this->department = new Department($this->department_id); }
				return $this->department;
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
		public function getEvents($date=null)
		{
			if ($this->id) { $search['calendar_id'] = $this->id; }
			if ($date)
			{
				if (isset($date['year'])) { $search['year'] = $date['year']; }
				if (isset($date['mon'])) { $search['mon'] = $date['mon']; }
				if (isset($date['mday'])) { $search['mday'] = $date['mday']; }
				if (isset($date['week'])) { $search['week'] = $date['week']; }
			}

			$eventList = new EventList();
			if (isset($search)) { $eventList->find($search); }
			else { $eventList->find(); }

			return $eventList;
		}
		public function getEventArray($date=null)
		{
			$this->eventArray = array();
			foreach($this->getEvents($date) as $event)
			{
				$e = $this->dateStringToArray($event->getStart());
				$this->eventArray[$e['year']][$e['mon']][$e['mday']][] = $event;
			}
			return $this->eventArray;
		}
		public function permitsEditingBy($user)
		{
			if ($user->hasRole(array('Administrator','Webmaster')) ||
				($user->hasRole('Content Creator') && $user->getDepartment_id()==$this->department_id))
			{ return true; }
			else { return false; }
		}

		/**
		 * Generic Setters
		 */
		public function setName($string) { $this->name = trim($string); }
		public function setDepartment_id($int) { $this->department = new Department($int); $this->department_id = $int; }
		public function setUser_id($int) { $this->user = new User($int); $this->user_id = $int; }

		public function setDepartment($department) { $this->department_id = $department->getId(); $this->department = $department; }
	}
?>