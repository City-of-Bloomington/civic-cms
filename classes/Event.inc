<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
	require_once '/var/www/libraries/iCal4PHP/Recur.inc';
	class Event extends ActiveRecord
	{
		private $id;
		private $start;
		private $end;
		private $created;
		private $modified;
		private $title;
		private $description;
		private $allDayEvent;
		private $rrule_freq;
		private $rrule_until;
		private $rrule_count;
		private $rrule_interval;
		private $rrule_byday;
		private $rrule_bymonthday;
		private $rrule_bysetpos;
		private $calendar_id;
		private $location_id;
		private $user_id;
		private $contact_name;
		private $contact_phone;
		private $contact_email;

		private $week_start_day = 'Sunday';

		private $calendar;
		private $location;
		private $user;

		private $sections = array();


		/**
		 * This will load all fields in the table as properties of this class.
		 * You may want to replace this with, or add your own extra, custom loading
		 */
		public function __construct($id=null)
		{
			$PDO = Database::getConnection();

			if ($id)
			{
				$f = ctype_digit($id) ? 'id' : 'title';
				$sql = "select id,unix_timestamp(start) as start,unix_timestamp(end) as end,
								unix_timestamp(created) as created,unix_timestamp(modified) as modified,
								title,description,allDayEvent,
								rrule_freq,unix_timestamp(rrule_until) as rrule_until,rrule_count,
								rrule_interval,rrule_byday,rrule_bymonthday,rrule_bysetpos,
								calendar_id,location_id,user_id,
								contact_name,contact_phone,contact_email
						from events where $f=?";
				$query = $PDO->prepare($sql);
				$query->execute(array($id));

				$result = $query->fetchAll(PDO::FETCH_ASSOC);
				if (!count($result)) { throw new Exception('events/unknownEvent'); }
				foreach($result[0] as $field=>$value) { if ($value) $this->$field = $value; }
			}
			else
			{
				# This is where the code goes to generate a new, empty instance.
				# Set any default values for properties that need it here
				$this->created = time();
				$this->user_id = $_SESSION['USER']->getId();
				$this->user = $_SESSION['USER'];
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
			if (!$this->title) { throw new Exception('missingTitle'); }


			$fields = array();
			$fields['start'] = $this->start ? date('Y-m-d H:i:s',$this->start) : null;
			$fields['end'] = $this->end ? date('Y-m-d H:i:s',$this->end) : null;
			$fields['created'] = date('Y-m-d H:i:s',$this->created);
			$fields['modified'] = time();
			$fields['title'] = $this->title ? $this->title : null;
			$fields['description'] = $this->description ? $this->description : null;
			$fields['allDayEvent'] = $this->allDayEvent ? $this->allDayEvent : null;
			$fields['rrule_freq'] = $this->rrule_freq ? $this->rrule_freq : null;
			$fields['rrule_until'] = $this->rrule_until ? date('Y-m-d H:i:s',$this->rrule_until) : null;
			$fields['rrule_count'] = $this->rrule_count ? $this->rrule_count : null;
			$fields['rrule_interval'] = $this->rrule_interval ? $this->rrule_interval : null;
			$fields['rrule_byday'] = $this->rrule_byday ? $this->rrule_byday : null;
			$fields['rrule_bymonthday'] = $this->rrule_bymonthday ? $this->rrule_bymonthday : null;
			$fields['rrule_bysetpos'] = $this->rrule_bysetpos ? $this->rrule_bysetpos : null;
			$fields['calendar_id'] = $this->calendar_id ? $this->calendar_id : null;
			$fields['location_id'] = $this->location_id ? $this->location_id : null;
			$fields['user_id'] = $_SESSION['USER']->getId();
			$fields['contact_name'] = $this->contact_name ? $this->contact_name : null;
			$fields['contact_phone'] = $this->contact_phone ? $this->contact_phone : null;
			$fields['contact_email'] = $this->contact_email ? $this->contact_email : null;

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
			$PDO = Database::getConnection();

			$sql = "update events set $preparedFields where id={$this->id}";
			$query = $PDO->prepare($sql);
			$query->execute($values);
		}

		private function insert($values,$preparedFields)
		{
			$PDO = Database::getConnection();

			$sql = "insert events set $preparedFields";
			$query = $PDO->prepare($sql);
			$query->execute($values);

			$this->id = $PDO->lastInsertID();
		}

		public function delete()
		{
			if ($this->id)
			{
				$PDO = Database::getConnection();
				$query = $PDO->prepare('delete from event_exceptions where event_id=?');
				$query->execute(array($this->id));

				$query = $PDO->prepare('delete from event_sections where event_id=?');
				$query->execute(array($this->id));

				$query = $PDO->prepare('delete from events where id=?');
				$query->execute(array($this->id));
			}
		}

		public function permitsEditingBy($user)
		{
			if (isset($this->calendar_id)) { return $this->getCalendar()->permitsEditingBy($user); }
			else return true;
		}

		/**
		 * Section Functions
		 */
		public function getSections()
		{
			if ($this->id)
			{
				if (!count($this->sections))
				{
					$PDO = Database::getConnection();

					$query = $PDO->prepare('select section_id from event_sections where event_id=?');
					$query->execute(array($this->id));
					$result = $query->fetchAll();

					foreach($result as $row) { $this->sections[$row['section_id']] = new Section($row['section_id']); }
				}
			}
			return $this->sections;
		}

		public function setSections(array $section_ids)
		{
			$this->sections = array();
			foreach($section_ids as $id) { $this->sections[$id] = new Section($id); }
		}

		public function saveSections()
		{
			if ($this->id)
			{
				$PDO = Database::getConnection();

				$query = $PDO->prepare('delete from event_sections where event_id=?');
				$query->execute(array($this->id));

				$query = $PDO->prepare('insert event_sections set event_id=?,section_id=?');
				foreach($this->sections as $id=>$section)
				{
					$query->execute(array($this->id,$id));
				}
			}
		}

		public function hasSection($section)
		{
			$id = ($section instanceof Section) ? $section->getId() : $section;
			return array_key_exists($id,$this->getSections());
		}


		public function isAllDayEvent() { return $this->allDayEvent ? true : false; }
		public function isRecurringEvent() { return $this->frequency ? true : false; }

		public function getRRule()
		{
			if ($this->rrule_freq)
			{
				$rrule = array();
				$rrule[] = 'FREQ='.$this->rrule_freq;
				if ($this->rrule_interval) { $rrule[] = 'INTERVAL='.$this->rrule_interval; }

				if ($this->rrule_until) { $rrule[] = 'UNTIL='.date('Ymd\THis',$this->rrule_until); }
				elseif ($this->rrule_count){ $rrule[] = 'COUNT='.$this->rrule_count; }

				if ($this->rrule_byday) { $rrule[] = 'BYDAY='.$this->rrule_byday; }
				if ($this->rrule_bymonthday) { $rrule[] = 'BYMONTHDAY='.$this->rrule_bymonthday; }
				if ($this->rrule_bysetpos) { $rrule[] = 'BYSETPOS='.$this->rrule_bysetpos; }
				$rrule = implode(';',$rrule);
				return $rrule;
			}
		}

		/**
		 * Returns an array of timestamps for the recurrences for this event that
		 * happen during the given time period
		 * @param timestamp $periodStart
		 * @param timestamp $periodEnd
		 */
		public function getRecurrences ($periodStart=null,$periodEnd=null)
		{
			if (!$periodStart) { $periodStart = $this->start; }
			if (!$periodEnd) { $periodEnd = $this->rrule_until ? $this->rrule_until : null; }

			$recurringEvents = array();

			if ($this->rrule_freq)
			{
				$recur = new Recur($this->getRRule());
				$dates = $recur->getDates($periodStart,$periodEnd,$this->start);
				foreach($dates as $date)
				{
					$start = getdate($this->start);
					$end = getdate($this->end);

					$r = new EventRecurrence($this,$date);
					$d = getdate($date);
					$r->setStart(mktime($start['hours'],$start['minutes'],$start['seconds'],$d['mon'],$d['mday'],$d['year']));
					$r->setEnd(mktime($end['hours'],$end['minutes'],$end['seconds'],$d['mon'],$d['mday'],$d['year']));
					$recurringEvents[] = $r;
				}
			}
			else
			{
				if ($periodStart <= $this->start && (!$periodEnd || $this->start <= $periodEnd))
				{
					$r = new EventRecurrence($this,$this->start);
					$r->setStart($this->start);
					$r->setEnd($this->end);
					$recurringEvents[] = $r;
				}
			}
			return $recurringEvents;
		}

		public function getURL() { return BASE_URL.'/calendars/viewEvent.php?event_id='.$this->id; }

		/**
		 * Generic Getters
		 */
		public function getId() { return $this->id; }
		public function getStart($format=null)
		{
			if ($format && $this->start)
			{
				if (strpos($format,'%')!==false) { return strftime($format,$this->start); }
				else { return date($format,$this->start); }
			}
			else return $this->start;
		}
		public function getEnd($format=null)
		{
			if ($format && $this->end)
			{
				if (strpos($format,'%')!==false) { return strftime($format,$this->end); }
				else { return date($format,$this->end); }
			}
			else return $this->end;
		}
		public function getCreated($format=null)
		{
			if ($format && $this->created)
			{
				if (strpos($format,'%')!==false) { return strftime($format,$this->created); }
				else { return date($format,$this->created); }
			}
			else return $this->created;
		}
		public function getModified($format=null)
		{
			if ($format && $this->modified)
			{
				if (strpos($format,'%')!==false) { return strftime($format,$this->modified); }
				else { return date($format,$this->modified); }
			}
			else return $this->modified;
		}
		public function getTitle() { return $this->title; }
		public function getDescription() { return $this->description; }
		public function getAllDayEvent() { return $this->allDayEvent; }
		public function getRrule_freq() { return $this->rrule_freq; }
		public function getRrule_until($format=null)
		{
			if ($format && $this->rrule_until)
			{
				if (strpos($format,'%')!==false) { return strftime($format,$this->rrule_until); }
				else { return date($format,$this->rrule_until); }
			}
			else return $this->rrule_until;
		}
		public function getRrule_count() { return $this->rrule_count; }
		public function getRrule_interval() { return $this->rrule_interval; }
		public function getRrule_byday() { return $this->rrule_byday; }
		public function getRrule_bymonthday() { return $this->rrule_bymonthday; }
		public function getRrule_bysetpos() { return $this->rrule_bysetpos; }
		public function getCalendar_id() { return $this->calendar_id; }
		public function getLocation_id() { return $this->location_id; }
		public function getUser_id() { return $this->user_id; }
		public function getContact_name() { return $this->contact_name; }
		public function getContact_phone() { return $this->contact_phone; }
		public function getContact_email() { return $this->contact_email; }

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

		private function validateFrequency()
		{
			if ($this->rrule_freq)
			{
				$valid = array('SECONDLY','MINUTELY','HOURLY','DAILY','WEEKLY','MONTHLY','YEARLY');
				if (!in_array($this->rrule_freq,$valid))
				{
					$this->rrule_freq = null;
					throw new Exception('events/invalidFreq');
				}
			}
		}
		/**
		 * Generic Setters
		 */
		public function setStart($datetime)
		{
			if (is_array($datetime)) { $this->start = $this->dateArrayToTimestamp($datetime); }
			elseif(ctype_digit($datetime)) { $this->start = $datetime; }
			else { $this->start = strtotime($datetime); }
		}
		public function setEnd($datetime)
		{
			if (is_array($datetime)) { $this->end = $this->dateArrayToTimestamp($datetime); }
			elseif(ctype_digit($datetime)) { $this->end = $datetime; }
			else { $this->end = strtotime($datetime); }
		}
		public function setCreated($datetime)
		{
			if (is_array($datetime)) { $this->created = $this->dateArrayToTimestamp($datetime); }
			elseif(ctype_digit($datetime)) { $this->created = $datetime; }
			else { $this->created = strtotime($datetime); }
		}
		public function setModified($datetime)
		{
			if (is_array($datetime)) { $this->modified = $this->dateArrayToTimestamp($datetime); }
			elseif(ctype_digit($datetime)) { $this->modified = $datetime; }
			else { $this->modified = strtotime($datetime); }
		}
		public function setTitle($string) { $this->title = trim($string); }
		public function setDescription($text) { $this->description = $text; }
		public function setAllDayEvent($int) { if ($int) $this->allDayEvent = 1; }
		public function setRrule_freq($string) { $this->rrule_freq = trim($string); $this->validateFrequency(); }
		public function setRrule_until($datetime)
		{
			if (is_array($datetime)) { $this->rrule_until = $this->dateArrayToTimestamp($datetime); }
			elseif(ctype_digit($datetime)) { $this->rrule_until = $datetime; }
			else { $this->rrule_until = strtotime($datetime); }

			# Until cannot happen before the end of the event.
			if ($this->rrule_until < $this->end) { $this->rrule_until = $this->end; }
		}
		public function setRrule_count($int) { $this->rrule_count = ereg_replace("[^0-9]","",$int); }
		public function setRrule_interval($int) { $this->rrule_interval = ereg_replace("[^0-9]","",$int); }
		public function setRrule_byday($string) { $this->rrule_byday = trim($string); }
		public function setRrule_bymonthday($string) { $this->rrule_bymonthday = trim($string); }
		public function setRrule_bysetpos($int) { $this->rrule_bysetpos = ereg_replace("[^0-9\-]","",$int); }
		public function setCalendar_id($int) { $this->calendar = new Calendar($int); $this->calendar_id = $int; }
		public function setLocation_id($int) { $this->location = new Location($int); $this->location_id = $int; }
		public function setUser_id($int) { $this->user = new User($int); $this->user_id = $int; }
		public function setContact_name($string) { $this->contact_name = trim($string); }
		public function setContact_phone($string) { $this->contact_phone = trim($string); }
		public function setContact_email($string) { $this->contact_email = trim($string); }

		public function setCalendar($calendar) { $this->calendar_id = $calendar->getId(); $this->calendar = $calendar; }
		public function setLocation($location) { $this->location_id = $location->getId(); $this->location = $location; }
		public function setUser($user) { $this->user_id = $user->getId(); $this->user = $user; }
	}
