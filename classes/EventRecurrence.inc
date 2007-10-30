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

		public function isEvent() { return $this->type == 'Event'; }
		public function isRecurrence() { return $this->type == 'Recurrence'; }

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
