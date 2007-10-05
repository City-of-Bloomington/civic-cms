<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
	class EventRecurrence extends ActiveRecord
	{
		private $event_id;
		private $original_start;
		private $start;
		private $end;
		private $event;
		private $type;

		public function __construct($event,$original_start)
		{
			$PDO = Database::getConnection();

			$this->event_id = $event->getId();
			$this->event = $event;
			$this->original_start = $original_start;

			if ($this->event->getStartDate() == $this->original_start) { $this->type = 'Event'; }
			else { $this->type = 'Recurrence'; }

			# Load any exception data for this recurrence
			$query = $PDO->prepare("select start,end from event_exceptions where event_id=? and original_start=?");
			$query->execute(array($this->event_id,$this->original_start));
			$result = $query->fetchAll();
			if (count($result))
			{
				$this->start = $result[0]['start'];
				$this->end = $result[0]['end'];
				$this->type = 'Exception';
			}
		}

		public function save()
		{
			if ($this->isException())
			{
				$PDO = Database::getConnection();
				$sql = "insert event_exceptions values($this->event_id,'$this->original_start','$this->start','$this->end')
						on duplicate key update start='$this->start',end='$this->end'";
				$query = $PDO->prepare($sql);
				$query->execute();
			}
		}

		public function isEvent() { return $this->type == 'Event'; }
		public function isRecurrence() { return $this->type == 'Recurrence'; }
		public function isException() { return $this->type == 'Exception'; }

		/**
		 * Generic Getters
		 */
		public function getEvent_id() { return $this->event_id; }
		public function getOriginal_start() { return $this->original_start; }
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
		public function getEvent() { return $this->event; }
		public function getType() { return $this->type; }

		/**
		 * Generic Setters
		 */
		public function setStart($datetime) { $this->start = is_array($datetime) ? $this->dateArrayToString($datetime) : $datetime; }
		public function setEnd($datetime) { $this->end = is_array($datetime) ? $this->dateArrayToString($datetime) : $datetime; }
	}
?>
