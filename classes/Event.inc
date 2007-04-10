<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
	class Event extends ActiveRecord
	{
		private $id;
		private $created;
		private $start;
		private $end;
		private $allDayEvent;
		private $rrule;
		private $summary;
		private $description;
		private $calendar_id;
		private $location_id;
		private $user_id;


		private $calendar;
		private $location;
		private $user;

		private $sections = array();
		private $newSectionIds = array();
		private $deletedSectionIds = array();

		/**
		 * This will load all fields in the table as properties of this class.
		 * You may want to replace this with, or add your own extra, custom loading
		 */
		public function __construct($id=null)
		{
			global $PDO;

			if ($id)
			{
				$sql = 'select * from events where id=?';
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
			if (!$this->start || !$this->summary || !$this->calendar_id || !$this->location_id) { throw new Exception('missingRequiredFields'); }

			# Event end time must come after the start time
			if ($this->end < $this->start) { throw new Exception('invalidEndTime'); }

			$fields = array();
			$fields['start'] = $this->start ? $this->start : null;
			$fields['end'] = $this->end ? $this->end : null;
			$fields['allDayEvent'] = $this->allDayEvent ? $this->allDayEvent : null;
			$fields['rrule'] = $this->rrule ? $this->rrule : null;
			$fields['summary'] = $this->summary ? $this->summary : null;
			$fields['description'] = $this->description ? $this->description : null;
			$fields['calendar_id'] = $this->calendar_id ? $this->calendar_id : null;
			$fields['location_id'] = $this->location_id ? $this->location_id : null;
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

			$this->saveSections();
		}

		private function update($values,$preparedFields)
		{
			global $PDO;

			$sql = "update events set $preparedFields where id={$this->id}";
			if (false === $query = $PDO->prepare($sql)) { $e = $PDO->errorInfo(); throw new Exception($sql.$e[2]); }
			if (false === $query->execute($values)) { $e = $PDO->errorInfo(); throw new Exception($sql.$e[2]); }
		}

		private function insert($values,$preparedFields)
		{
			global $PDO;

			$sql = "insert events set $preparedFields";
			if (false === $query = $PDO->prepare($sql)) { $e = $PDO->errorInfo(); throw new Exception($sql.$e[2]); }
			if (false === $query->execute($values)) { $e = $PDO->errorInfo(); throw new Exception($sql.$e[2]); }
			$this->id = $PDO->lastInsertID();
		}

		public function permitsEditingBy($user)
		{
			return $this->getCalendar()->permitsEditingBy($user);
		}

		/**
		 * Section functions
		 */
		public function getSections()
		{
			global $PDO;

			if (!count($this->sections) && $this->id)
			{
				$sql = "select section_id from event_sections where event_id={$this->id}";
				$query = $PDO->query($sql);
				foreach($query->fetchAll() as $row)
				{
					$this->sections[$row['section_id']] = new Section($row['section_id']);
				}
			}
			return $this->sections;
		}
		public function setSections(array $sectionIds)
		{
			# Make sure to call $this->getSections() at least once to ensure that
			# the current sections are loaded before trying to determine which ones are new

			# Only load the new sections the user is allowed to edit
			$newSections = array();
			foreach($sectionIds as $id)
			{
				$section = new Section($id);
				if ($section->permitsEditingBy($_SESSION['USER'])) { $newSections[$id] = $section; }
			}

			# Any Sections that are not in $this->sections need to be added
			$this->newSections = array_diff_key($newSections,$this->getSections());
			foreach($this->newSections as $id=>$section) { $this->sections[$id] = $section; }

			# Unset any $this->sections that are not in $sectionIds
			$this->deletedSections = array_diff_key($this->sections,$newSections);
			foreach($this->deletedSections as $id=>$section) { unset($this->sections[$id]); }
		}
		private function saveSections()
		{
			global $PDO;

			# Clear out any deleted sections
			if (count($this->deletedSections))
			{
				$deletedSections = implode(",",array_keys($this->deletedSections));
				$query = $PDO->prepare("delete from event_sections where event_id={$this->id} and section_id in ($deletedSections)");
				$query->execute();
			}

			# Add in any new sections
			if (count($this->newSections))
			{
				$query = $PDO->prepare("insert event_sections values($this->id,?)");
				foreach($this->newSections as $id=>$section) { $query->execute(array($id)); }
			}
		}
		public function hasSection($section) { return array_key_exists($section->getId(),$this->getSections()); }

		public function isAllDayEvent() { return $this->allDayEvent; }


		/**
		 * Generic Getters
		 */
		public function getId() { return $this->id; }
		public function getCreated($format=null)
		{
			if ($format && $this->created!=0) return strftime($format,strtotime($this->created));
			else return $this->created;
		}
		public function getStart($format=null)
		{
			if ($format && $this->start!=0) return strftime($format,strtotime($this->start));
			else return $this->start;
		}
		public function getEnd($format=null)
		{
			if ($format && $this->end!=0) return strftime($format,strtotime($this->end));
			else return $this->end;
		}
		public function getRRule() { return $this->rrule; }
		public function getSummary() { return $this->summary; }
		public function getDescription() { return $this->description; }
		public function getCalendar_id() { return $this->calendar_id; }
		public function getLocation_id() { return $this->location_id; }
		public function getUser_id() { return $this->user_id; }

		public function getCalendar()
		{
			if ($this->calendar_id)
			{
				if (!$this->calendar) { $this->calendar = new Calendar($this->calendar_id); }
				return $this->calendar;
			}
			else return null;
		}

		public function getLocation()
		{
			if ($this->location_id)
			{
				if (!$this->location) { $this->location = new Location($this->location_id); }
				return $this->location;
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
		public function setStart($datetime) { $this->start = is_array($datetime) ? $this->dateArrayToString($datetime) : $datetime; }
		public function setEnd($datetime) { $this->end = is_array($datetime) ? $this->dateArrayToString($datetime) : $datetime; }
		public function setAllDayEvent($int) { $this->allDayEvent = $int ? 1 : 0; }
		public function setRRule($string) { $this->rrule = trim($string); }
		public function setSummary($string) { $this->summary = trim($string); }
		public function setDescription($text) { $this->description = $text; }
		public function setCalendar_id($int) { $this->calendar = new Calendar($int); $this->calendar_id = $int; }
		public function setLocation_id($int) { $this->location = new Location($int); $this->location_id = $int; }
		public function setUser_id($int) { $this->user = new User($int); $this->user_id = $int; }

		public function setCalendar($calendar) { $this->calendar_id = $calendar->getId(); $this->calendar = $calendar; }
		public function setLocation($location) { $this->location_id = $location->getId(); $this->location = $location; }
	}
?>