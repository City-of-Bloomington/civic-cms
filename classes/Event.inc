<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
	class Event extends ActiveRecord
	{
		private $id;
		private $created;
		private $startDate;
		private $startTime;
		private $endDate;
		private $endTime;
		private $allDayEvent;
		private $rrule;
		private $summary;
		private $description;
		private $calendar_id;
		private $location_id;
		private $user_id;
		private $contact_name;
		private $contact_phone;
		private $contact_email;


		private $calendar;
		private $location;
		private $user;

		private $sections = array();
		private $deletedSections = array();
		private $newSections = array();

		/**
		 * This will load all fields in the table as properties of this class.
		 * You may want to replace this with, or add your own extra, custom loading
		 */
		public function __construct($id=null)
		{
			if ($id)
			{
				$PDO = Database::getConnection();
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
			if (!$this->startDate || !$this->summary || !$this->calendar_id) { throw new Exception('missingRequiredFields'); }

			# Event end time must come after the start time
			if ($this->endDate)
			{
				if (strtotime("{$this->endDate} {$this->endTime}") < strtotime("{$this->startDate} {$this->startTime}"))
				{
					throw new Exception('invalidEndTime');
				}
			}

			$fields = array();
			$fields['startDate'] = $this->startDate ? $this->startDate : null;
			$fields['startTime'] = $this->startTime ? $this->startTime : null;
			$fields['endDate'] = $this->endDate ? $this->endDate : null;
			$fields['endTime'] = $this->endTime ? $this->endTime : null;
			$fields['allDayEvent'] = $this->allDayEvent ? $this->allDayEvent : null;
			$fields['rrule'] = $this->rrule ? $this->rrule : null;
			$fields['summary'] = $this->summary ? $this->summary : null;
			$fields['description'] = $this->description ? $this->description : null;
			$fields['calendar_id'] = $this->calendar_id ? $this->calendar_id : null;
			$fields['location_id'] = $this->location_id ? $this->location_id : null;
			$fields['user_id'] = $this->user_id ? $this->user_id : $_SESSION['USER']->getId();
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
			if (false === $query = $PDO->prepare($sql)) { $e = $PDO->errorInfo(); throw new Exception($sql.$e[2]); }
			if (false === $query->execute($values)) { $e = $PDO->errorInfo(); throw new Exception($sql.$e[2]); }
		}

		private function insert($values,$preparedFields)
		{
			$PDO = Database::getConnection();

			$sql = "insert events set $preparedFields";
			echo "$sql\n";
			print_r($values);
			if (false === $query = $PDO->prepare($sql)) { $e = $PDO->errorInfo(); throw new Exception($sql.$e[2]); }
			if (false === $query->execute($values)) { $e = $PDO->errorInfo(); throw new Exception($sql.$e[2]); }
			$this->id = $PDO->lastInsertID();
		}

		public function permitsEditingBy($user)
		{
			if (isset($this->calendar_id)) { return $this->getCalendar()->permitsEditingBy($user); }
			else return true;
		}

		/**
		 * Section functions
		 */
		public function getSections()
		{
			if (!count($this->sections) && $this->id)
			{
				$PDO = Database::getConnection();
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
			$PDO = Database::getConnection();

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

		public function setRRule($rrule)
		{
			if (is_array($rrule))
			{
				if ($rrule['FREQ'])
				{
					switch ($rrule['FREQ'])
					{
						case 'DAILY':
							$this->rrule = 'FREQ=DAILY';
							$i = ereg_replace('[^0-9]','',$rrule['DAILY']['INTERVAL']);
							if ($i) { $this->rrule.= ";INTERVAL=$i"; }
						break;

						case 'WEEKLY':
							$this->rrule = 'FREQ=WEEKLY';
							$i = ereg_replace('[^0-9]','',$rrule['WEEKLY']['INTERVAL']);
							if ($i) { $this->rrule.= ";INTERVAL=$i"; }
							if (isset($rrule['WEEKLY']['BYDAY']))
							{
								$byday = implode(',',array_keys($rrule['WEEKLY']['BYDAY']));
								$this->rrule.= ";BYDAY=$byday";
							}
						break;

						case 'MONTHLY':
							$this->rrule = 'FREQ=MONTHLY';
							switch ($rrule['MONTHLY']['type'])
							{
								case 'BYMONTHDAY':
									$i = ereg_replace('[^0-9]','',$rrule['MONTHLY']['BYMONTHDAY']['INTERVAL']);
									if ($i) { $this->rrule.= ";INTERVAL=$i"; }
									$bymonthday = ereg_replace('[^0-9\-]','',$rrule['MONTHLY']['BYMONTHDAY']['DAYNUM']);
									if ($bymonthday) { $this->rrule.= ";BYMONTHDAY=$bymonthday"; }
								break;

								case 'BYDAY':
									$i = ereg_replace('[^0-9]','',$rrule['MONTHLY']['BYDAY']['INTERVAL']);
									if ($i) { $this->rrule.= ";INTERVAL=$i"; }
									$byday = $rrule['MONTHLY']['BYDAY']['weekdaynum'].$rrule['MONTHLY']['BYDAY']['weekday'];
									$this->rrule.= ";BYDAY=$byday";
								break;
							}
						break;
					}
				}
			}
			else { $this->rrule = trim($string); }
		}

		public function getRecurrences ($start_range_time=null,$end_range_time=null)
		{
			if (!$start_range_time) { $start_range_time = strtotime("{$this->startDate} {$this->startTime}"); }
			if (!$end_range_time)
			{
				$end_range_time = $this->endDate ? strtotime("{$this->endDate} {$this->endTime}") : strtotime("+1 day",$start_range_time);
			}

			$recurringEvents = array();
			if ($this->rrule)
			{
				$start_date_time = strtotime("{$this->startDate} {$this->startTime}");
				$end_date_time = $this->endDate ? strtotime("{$this->endDate} {$this->endTime}") : $end_range_time;

				# We need an array of all the RRULES
				$recur_data = array();
				$rrule_array = array();
				$rrule = explode(';',$this->rrule);
				foreach($rrule as $rule)
				{
					list($key,$value) = explode('=',$rule);

					switch ($key)
					{
						case 'FREQ':
							switch ($value)
							{
								case 'YEARLY':	$freq_type = 'year';	break;
								case 'MONTHLY':	$freq_type = 'month';	break;
								case 'WEEKLY':	$freq_type = 'week';	break;
								case 'DAILY':	$freq_type = 'day';		break;
								default:
							}
							# The default INTERVAL is 1
							$interval = 1;
						break;

						case 'INTERVAL':
							$interval = $value;
						break;

						case 'BYDAY':
							$byday = split(',',$value);
						break;

						case 'BYMONTHDAY':
							$bymonthday = split(',',$value);
						break;

						case 'BYMONTH':
							$bymonth = split(',',$value);
						break;
					}
				}

				// If the $end_range_time is less than the $start_date_time, or $start_range_time is greater
				// than $end_date_time, we may as well forget the whole thing
				// It doesn't do us any good to spend time adding data we aren't even looking at
				// this will prevent the year view from taking way longer than it needs to
				if ($end_range_time >= $start_date_time && $start_range_time <= $end_date_time)
				{
					if ($start_range_time < $start_date_time) { $start_range_time = $start_date_time; }
					if ($end_range_time > $end_date_time) { $end_range_time = $end_date_time; }


					$next_range_time = $start_range_time;
					while($next_range_time <= $end_range_time)
					{
						# What is the interval between $next_range_time and $start_date_time
						$compare = $freq_type.'Compare';
						$diff = $this->$compare($next_range_time,$start_date_time);

						if ($diff % $interval == 0)
						{
							switch ($freq_type)
							{
								case 'day':
									$recur_data[] = $next_range_time;
								break;

								case 'week':
									# Get the sunday of the current week
									$d = date('w',$next_range_time);
									$sunday = strtotime("-$d days",$next_range_time);

									if (!isset($byday))
									{
										# Use the day of the week from $start_date_time
										$byday = array(strtoupper(substr(date('l',$start_date_time),0,2)));
									}
									foreach($byday as $day)
									{
										# strtotime needs at least three letters for the day
										# RRULES only use two letters
										$next_date_time = strtotime($this->two2threeCharDays($day),$sunday+(12*60*60));

										# Reset the $next_range_time to the first instance of the week
										if ($next_date_time < $next_range_time) { $next_range_time = $next_date_time; }

										$recur_data[] = $next_date_time;
									}
								break;

								case 'month':
									if (!isset($bymonth)) { $bymonth = array(1,2,3,4,5,6,7,8,9,10,11,12); }

									# Go to the first day of the month
									$d = getdate($next_range_time);
									$next_range_time = strtotime("$d[year]-$d[mon]-1");

									if (isset($bymonthday))
									{
										foreach($bymonthday as $day)
										{
											# Convert the negative monthdays into the actual daynum
											if ($day < 0) { $day = date('t',$next_range_time) + $day + 1; }

											if (checkdate($d['mon'],$day,$d['year']))
											{
												$recur_data[] = mktime(0,0,0,$d['mon'],$day,$d['year']);
											}

										}
									}
									elseif (isset($byday))
									{
										foreach($byday as $day)
										{
											$nth = substr($day,0,-2);
											$day = substr($day,-2);
											$day_num = $this->two2threeCharDays($day,false);
											$day = $this->two2threeCharDays($day);

											if ($nth < 0)
											{
												$last_day = date('t',$next_range_time);
												$next_range_time = strtotime(date("Y-m-$last_day",$next_range_time));

												$last = (date('w',$next_range_time) == $day_num) ? '' : 'last ';
												$next_range_time = strtotime("$last$day",$next_range_time) - (abs($nth)-1) * 604800;

												$month = date('m',$next_range_time);
												if (in_array(date('m',$next_range_time),$bymonth))
												{
													$recur_data[] = $next_range_time;
												}

												# Reset to the start of the month
												$next_range_time = strtotime(date('Y-m-1',$next_range_time));
											}
											else
											{
												$next_date_time = strtotime($day,$next_range_time) + ($nth-1) * 604800;
												if (in_array(date('m',$next_date_time),$bymonth))
												{
													$recur_data[] = $next_date_time;
												}
											}

										}
									}
								break;
							}
						}

						$next_range_time = strtotime("+$interval $freq_type",$next_range_time);
					}
				}

				# Recur_data now has dates set.
				# We still need to add Time information from the event
				foreach($recur_data as $key=>$recurrence)
				{
					$date = date('Y-m-d',$recurrence);

					# If there's not an exception for this recurrence, set the start and end
					$r = new EventRecurrence($this,$date);
					if (!$r->isException())
					{
						$r->setStart("$date {$this->startTime}");
						$r->setEnd("$date {$this->endTime}");
					}
					$recurringEvents[] = $r;
				}
			}
			else
			{
				# There are no recurring events.  Just return the event's info
				# But only if it's inside the range
				$datetime = strtotime("{$this->startDate} {$this->startTime}");
				if ($start_range_time <= $datetime && $datetime <= $end_range_time)
				{
					$r = new EventRecurrence($this,$this->startDate);
					$r->setStart("{$this->startDate} {$this->startTime}");
					$r->setEnd("{$this->endDate} {$this->endTime}");
					$recurringEvents[] = $r;
				}
			}
			return $recurringEvents;
		}

		# Returns the number of weeks between two timestamps
		private function weekCompare($now, $then)
		{
			# Get the timestamps for the sundays
			$d = date('w',$now);
			$sunday_now = strtotime("-$d days",$now);

			$d = date('w',$then);
			$sunday_then = strtotime("-$d days",$then);

			return round(($sunday_now - $sunday_then)/(60*60*24*7));
		}

		# Returns the nuimber of days between two timestamps
		private function dayCompare($now, $then) { return round(((($now-$then)/60)/60)/24); }

		# Returns the number of months between two datse
		private function monthCompare($now, $then)
		{
			$now = getdate($now);
			$then = getdate($then);

			$years = $now['year'] - $then['year'];
			$months = $now['mon'] - $then['mon'];
			if ($now['mon'] < $then['mon'])
			{
				$years--;
				$months = ($months + 12) % 12;
			}
			return ($years * 12) + $months;
		}

		// takes iCalendar 2 day format and makes it into 3 characters
		// if $txt is true, it returns the 3 letters, otherwise it returns the
		// integer of that day; 0=Sun, 1=Mon, etc.
		private function two2threeCharDays($day, $txt=true)
		{
			switch($day)
			{
				case 'SU': return ($txt ? 'sun' : '0');
				case 'MO': return ($txt ? 'mon' : '1');
				case 'TU': return ($txt ? 'tue' : '2');
				case 'WE': return ($txt ? 'wed' : '3');
				case 'TH': return ($txt ? 'thu' : '4');
				case 'FR': return ($txt ? 'fri' : '5');
				case 'SA': return ($txt ? 'sat' : '6');
			}
		}


		/**
		 * Generic Getters
		 */
		public function getId() { return $this->id; }
		public function getCreated($format=null)
		{
			if ($format && $this->created!=0) return strftime($format,strtotime($this->created));
			else return $this->created;
		}
		public function getStartDate($format=null)
		{
			if ($format && $this->startDate!=0) return strftime($format,strtotime($this->startDate));
			else return $this->startDate;
		}
		public function getStartTime() { return $this->startTime; }
		public function getEndDate($format=null)
		{
			if ($format && $this->endDate!=0) return strftime($format,strtotime($this->endDate));
			else return $this->endDate;
		}
		public function getEndTime() { return $this->endTime; }
		public function getAllDayEvent() { return $this->allDayEvent; }
		public function getRRule() { return $this->rrule; }
		public function getRRuleArray()
		{
			$rruleArray = array();
			if ($this->rrule)
			{
				$rrule = explode(';',$this->rrule);
				foreach($rrule as $rule)
				{
					list($field,$value) = explode('=',$rule);
					switch($field)
					{
						case 'FREQ': $rruleArray['FREQ'] = $value; break;
						case 'INTERVAL': $rruleArray['INTERVAL'] = $value; break;
						case 'BYMONTHDAY': $rruleArray['BYMONTHDAY'] = $value; break;
						case 'BYDAY': $rruleArray['BYDAY'] = explode(',',$value); break;
					}
				}
			}
			return $rruleArray;
		}
		public function getSummary() { return $this->summary; }
		public function getDescription() { return $this->description; }
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


		/**
		 * Generic Setters
		 */
		public function setStartDate($date) { $this->startDate = is_array($date) ? $this->dateArrayToString($date) : date('Y-m-d',strtotime($date)); }
		public function setStartTime($time) { $this->startTime = $time ? date('H:i:s',strtotime($time)) : ''; }
		public function setEndDate($date) { $this->endDate = is_array($date) ? $this->dateArrayToString($date) : date('Y-m-d',strtotime($date)); }
		public function setEndTime($time) { $this->endTime = $time ? date('H:i:s',strtotime($time)) : ''; }
		public function setAllDayEvent($int) { $this->allDayEvent = $int ? 1 : 0; }
		public function setSummary($string) { $this->summary = trim($string); }
		public function setDescription($text) { $this->description = $text; }
		public function setCalendar_id($int) { $this->calendar = new Calendar($int); $this->calendar_id = $int; }
		public function setLocation_id($int) { $this->location = new Location($int); $this->location_id = $int; }
		public function setUser_id($int) { $this->user = new User($int); $this->user_id = $int; }
		public function setContact_name($string) { $this->contact_name = trim($string); }
		public function setContact_phone($string) { $this->contact_phone = trim($string); }
		public function setContact_email($string) { $this->contact_email = trim($string); }

		public function setCalendar($calendar) { $this->calendar_id = $calendar->getId(); $this->calendar = $calendar; }
		public function setLocation($location) { $this->location_id = $location->getId(); $this->location = $location; }
	}
?>
