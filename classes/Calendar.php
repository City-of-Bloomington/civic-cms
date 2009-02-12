<?php
/**
 * @copyright Copyright (C) 2006-2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
class Calendar extends ActiveRecord
{
	private $id;
	private $name;
	private $description;
	private $user_id;

	private $user;
	private $departments = array();
	private $newDepartments = array();
	private $deletedDepartments = array();


	/**
	 * This will load all fields in the table as properties of this class.
	 * You may want to replace this with, or add your own extra, custom loading
	 */
	public function __construct($id=null)
	{
		if ($id)
		{
			$PDO = Database::getConnection();
			if (is_numeric($id)) { $sql = 'select * from calendars where id=?'; }
			else { $sql = 'select * from calendars where name=?'; }

			$query = $PDO->prepare($sql);
			$query->execute(array($id));

			$result = $query->fetchAll();
			if (!count($result)) { throw new Exception('calendars/unknownCalendar'); }
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
		if (!$this->name) { throw new Exception('missingName'); }
		if (!$this->description) { throw new Exception('missingDescription'); }

		$fields = array();
		$fields['name'] = $this->name ? $this->name : null;
		$fields['description'] = $this->description ? $this->description : null;
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

		$this->saveDepartments();
	}

	private function update($values,$preparedFields)
	{
		$PDO = Database::getConnection();

		$sql = "update calendars set $preparedFields where id={$this->id}";
		$query = $PDO->prepare($sql);
		$query->execute($values);
	}

	private function insert($values,$preparedFields)
	{
		$PDO = Database::getConnection();

		$sql = "insert calendars set $preparedFields";
		$query = $PDO->prepare($sql);
		$query->execute($values);
		$this->id = $PDO->lastInsertID();
	}

	private function fold($string) { return trim(preg_replace("/(.{1,72})/i","\\1\r\n ",trim($string))); }

	/**
	 * Department functions
	 */
	public function hasDepartment($department)
	{
		return array_key_exists($department->getId(),$this->getDepartments());
	}
	public function getDepartments()
	{
		# A Calendar cannot have departments until it has an ID
		if (!count($this->departments) && $this->id)
		{
			$list = new DepartmentList(array('calendar_id'=>$this->id));
			foreach($list as $department) { $this->departments[$department->getId()] = $department; }
		}
		return $this->departments;
	}
	public function setDepartments(array $departmentIds)
	{
		# Make sure to call $this->getDepartments() at least once to ensure that
		# the current departments are loaded before trying to determine which ones are new

		$newDepartments = array();
		foreach($departmentIds as $id) { $newDepartments[$id] = new Department($id); }

		# Any Departments that are not in $this->departments need to be added
		$this->newDepartments = array_diff_key($newDepartments,$this->getDepartments());
		foreach($this->newDepartments as $id=>$department) { $this->departments[$id] = $department; }

		# Unset any $this->departments that are not in $departmentIds
		$this->deletedDepartments = array_diff_key($this->departments,$newDepartments);
		foreach($this->deletedDepartments as $id=>$department) { unset($this->departments[$id]); }
	}
	private function saveDepartments()
	{
		$PDO = Database::getConnection();

		# Clear out any deleted departments
		if (count($this->deletedDepartments))
		{
			$deletedDepartments = implode(",",array_keys($this->deletedDepartments));
			$query = $PDO->prepare("delete from calendar_departments where calendar_id={$this->id} and department_id in ($deletedDepartments)");
			$query->execute();
		}

		# Add in any new departments
		if (count($this->newDepartments))
		{
			$query = $PDO->prepare("insert calendar_departments values({$this->id},?)");
			foreach($this->newDepartments as $id=>$department) { $query->execute(array($id)); }
		}
	}

	/**
	 * Determines whether the user is allowed to make changes to the calendar.
	 * For example, changing it's name or department.
	 * This does not determine whether the user is allowed to post events to
	 * this calendar.
	 * @param User $user
	 */
	public function permitsEditingBy($user)
	{
		return $user->hasRole(array('Administrator','Webmaster'));
	}

	/**
	 * Determines whether the user is allowed to post events to this calendar
	 * @param User $user
	 */
	public function permitsPostingBy($user)
	{
		return ($user->hasRole(array('Administrator','Webmaster')) ||
			($user->hasRole('Content Creator') && $this->hasDepartment($user->getDepartment())));
	}


	/**
	 * Returns all the events in between rangeStart and rangeEnd, if given
	 * Or just on rangeStart.  $rangeStart and $rangeEnd must be given
	 * in the same format.
	 * @param timestamp $rangeStart
	 * @param timestamp $rangeEnd
	 * @param array $search Additional search terms
	 */
	public function getEvents($rangeStart=null,$rangeEnd=null,$search=null)
	{
		if (!is_array($search)) { $search = array(); }

		if ($this->id) { $search['calendar_id'] = $this->id; }
		if (isset($rangeStart))
		{
			$search['rangeStart'] = $rangeStart;
			if (isset($rangeEnd)) { $search['rangeEnd'] = $rangeEnd; }
		}

		$eventList = new EventList();
		if (count($search)) { $eventList->find($search); }
		else { $eventList->find(); }

		return $eventList;
	}
	/**
	 * Returns all the events with the recurrences exploded into
	 * an array, split up by year,month, and day
	 * Events will be between rangeStart and rangeEnd, if given
	 * or just on rangeStart.  $rangeStart and $rangeEnd must be given
	 * in the same format.
	 * @param timestamp $rangeStart
	 * @param timestamp $rangeEnd
	 * @param array $search Additional search terms
	 */
	public function getEventRecurrenceArray($rangeStart=null,$rangeEnd=null,$search=null)
	{
		$recurrenceArray = array();
		foreach($this->getEvents($rangeStart,$rangeEnd,$search) as $event)
		{
			foreach($event->getRecurrences($rangeStart,$rangeEnd) as $recurrence)
			{
				$r = getdate($recurrence->getStart());
				$recurrenceArray[$r['year']][$r['mon']][$r['mday']][] = $recurrence;
			}
		}

		// Sort the array before we return it.  The recurrences for each day
		// were added randomly and are not in order based on their start time
		foreach ($recurrenceArray as $year=>$monthArray) {
			foreach ($monthArray as $month=>$dayArray) {
				$days = array_keys($dayArray);
				foreach ($days as $day) {
					usort($recurrenceArray[$year][$month][$day],
						  array('Calendar','compareRecurrences'));
				}
			}
		}

		return $recurrenceArray;
	}
	public static function compareRecurrences(EventRecurrence $a,EventRecurrence $b)
	{
		if ($a->getStart() == $b->getStart()) {
			return 0;
		}
		return ($a->getStart() < $b->getStart()) ? -1 : 1;
	}

	public function getURL()
	{
		return BASE_URL.'/calendars?calendar_id='.$this->id;
	}

	/**
	 * Generic Getters
	 */
	public function getId() { return $this->id; }
	public function getName() { return $this->name; }
	public function getDescription() { return $this->description; }
	public function getUser_id() { return $this->user_id; }
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
	public function setName($string) { $this->name = trim($string); }
	public function setDescription($string) { $this->description = trim($string); }
	public function setUser_id($int) { $this->user = new User($int); $this->user_id = $int; }
}
