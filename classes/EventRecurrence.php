<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
	class EventRecurrence
	{
		private $event_id;
		private $original_start;
		private $start;
		private $end;
		private $event;
		private $type = 'Event';

		public function __construct($event,$original_start)
		{
			$this->event_id = $event->getId();
			$this->event = $event;
			if (is_numeric($original_start) && strlen($original_start)==10) { $this->original_start = $original_start; }
			else { $this->original_start = strtotime($original_start); }
		}

		/**
		 * Returns true if this is a single occurence of a non-recurring event
		 */
		public function isEvent() { return $this->type == 'Event'; }

		/**
		 * Returns true if this is a single occurence of a recurring event
		 */
		public function isRecurrence() { return $this->type == 'Recurrence'; }

		/**
		 * Aliases for event functions
		 * We want code to be able to work with EventRecurrences
		 * in the same way it would work with Events.  For information
		 * this EventRecurrence doesn't store, we provide these aliases
		 * to the Event's function
		 */
		public function permitsEditingBy($user) { return $this->event->permitsEditingBy($user); }
		public function isAllDayEvent() { return $this->event->isAllDayEvent(); }
		public function isRecurringEvent() { return $this->event->isRecurringEvent(); }
		public function getRRule() { return $this->event->getRRule(); }
		public function getLocation() { return $this->event->getLocation(); }
		public function getContact_name() { return $this->event->getContact_name(); }
		public function getContact_phone() { return $this->event->getContact_phone(); }
		public function getContact_email() { return $this->event->getContact_email(); }
		public function getDescription() { return $this->event->getDescription(); }
		public function getTitle() { return $this->event->getTitle(); }

		/**
		 * Returns the URL to see this on the site
		 * Helps make an EventRecurrence work the same as an Event
		 */
		public function getURL()
		{
			return BASE_URL."/calendars/viewEvent.php?event_id={$this->event_id};date=".$this->getStart('Y-m-d');
		}

		/**
		 * Alias for getEvent_id
		 * This helps make an EventRecurrence work the same as an Event
		 */
		public function getId() { return $this->getEvent_id(); }

		/**
		 * Generic Getters
		 */
		public function getEvent_id() { return $this->event_id; }
		public function getOriginal_start($format=null)
		{
			if ($format && $this->original_start)
			{
				if (strpos($format,'%')!==false) { return strftime($format,strtotime($this->original_start)); }
				else { return date($format,$this->original_start); }
			}
			else { return $this->original_start; }
		}
		public function getStart($format=null)
		{
			if ($format && $this->start)
			{
				if (strpos($format,'%')!==false) { return strftime($format,strtotime($this->start)); }
				else { return date($format,$this->start); }
			}
			else { return $this->start; }
		}
		public function getEnd($format=null)
		{
			if ($format && $this->end)
			{
				if (strpos($format,'%')!==false) { return strftime($format,strtotime($this->end)); }
				else { return date($format,$this->end); }
			}
			else { return $this->end; }
		}
		public function getEvent() { return $this->event; }
		public function getType() { return $this->type; }

		/**
		 * Generic Setters
		 */
		public function setStart($datetime)
		{
			if (is_array($datetime)) { $this->start = $this->dateArrayToTimestamp($datetime); }
			elseif(ctype_digit($datetime)) { $this->start = $datetime; }
			else { $this->start = strtotime($datetime); }

			if ($this->start != $this->original_start) { $this->type = 'Recurrence'; }
		}
		public function setEnd($datetime)
		{
			if (is_array($datetime)) { $this->end = $this->dateArrayToTimestamp($datetime); }
			elseif(ctype_digit($datetime)) { $this->end = $datetime; }
			else { $this->end = strtotime($datetime); }
		}
	}
