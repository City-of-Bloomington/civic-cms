<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
	class CalendarList extends PDOResultIterator
	{

		public function __construct($fields=null,$sort="id")
		{
			$this->select = "select calendars.id as id from calendars";
			$this->sort = $sort;
			if (is_array($fields)) $this->find($fields);
		}
	

		public function find($fields=null,$sort="id")
		{
			$this->sort = $sort;

			$options = array();
			if (isset($fields['id'])) { $options[] = "id='$fields[id]'"; }
			if (isset($fields['name'])) { $options[] = "name='$fields[name]'"; }
			if (isset($fields['department_id'])) { $options[] = "department_id='$fields[department_id]'"; }
			if (isset($fields['user_id'])) { $options[] = "user_id='$fields[user_id]'"; }


			# Finding on fields from other tables required joining those tables.
			# You can add fields from other tables to $options by adding the join SQL
			# to $this->joins here

			$this->populateList($options);
		}
	

		protected function loadResult($key) { return new Calendar($this->list[$key]); }
	}
?>