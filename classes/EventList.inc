<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
	class EventList extends PDOResultIterator
	{

		public function __construct($fields=null,$sort='id')
		{
			$this->select = 'select events.id as id from events';
			$this->sort = $sort;
			if (is_array($fields)) $this->find($fields);
		}


		public function find($fields=null,$sort='id')
		{
			$this->sort = $sort;

			$options = array();
			if (isset($fields['id'])) { $options[] = "id='$fields[id]'"; }
			if (isset($fields['created'])) { $options[] = "created='$fields[created]'"; }
			if (isset($fields['start'])) { $options[] = "start='$fields[start]'"; }
			if (isset($fields['end'])) { $options[] = "end='$fields[end]'"; }
			if (isset($fields['summary'])) { $options[] = "summary='$fields[summary]'"; }
			if (isset($fields['description'])) { $options[] = "description='$fields[description]'"; }
			if (isset($fields['calendar_id'])) { $options[] = "calendar_id='$fields[calendar_id]'"; }
			if (isset($fields['location_id'])) { $options[] = "location_id='$fields[location_id]'"; }
			if (isset($fields['user_id'])) { $options[] = "user_id='$fields[user_id]'"; }

			if (isset($fields['year'])) { $options[] = "year(start)='$fields[year]'"; }
			if (isset($fields['mon'])) { $options[] = "month(start)='$fields[mon]'"; }
			if (isset($fields['mday'])) { $options[] = "dayofmonth(start)='$fields[mday]'"; }
			if (isset($fields['week'])) { $options[] = "week(start)='$fields[week]'"; }

			# Finding on fields from other tables required joining those tables.
			# You can add fields from other tables to $options by adding the join SQL
			# to $this->joins here

			$this->populateList($options);
		}


		protected function loadResult($key) { return new Event($this->list[$key]); }
	}
?>