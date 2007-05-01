<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
	class EventList extends PDOResultIterator
	{

		public function __construct($fields=null,$sort=null,$limit=null,$groupBy=null)
		{
			$this->select = 'select events.id as id from events';
			if (is_array($fields)||$sort||$limit||$groupBy)
			{
				$this->find($fields,$sort,$limit,$groupBy);
			}
		}


		public function find($fields=null,$sort='id',$limit=null,$groupBy=null)
		{
			$this->sort = $sort;
			$this->limit = $limit;
			$this->groupBy = $groupBy;

			$options = array();
			if (isset($fields['id'])) { $options[] = "id='$fields[id]'"; }
			if (isset($fields['created'])) { $options[] = "created='$fields[created]'"; }
			if (isset($fields['startDate'])) { $options[] = "startDate='$fields[startDate]'"; }
			if (isset($fields['startTime'])) { $options[] = "startTime='$fields[startTime]'"; }
			if (isset($fields['endDate'])) { $options[] = "endDate='$fields[endDate]'"; }
			if (isset($fields['endTime'])) { $options[] = "endTime='$fields[endTime]'"; }
			if (isset($fields['allDayEvent'])) { $options[] = "allDayEvent='$fields[allDayEvent]'"; }
			if (isset($fields['rrule'])) { $options[] = "rrule='$fields[rrule]'"; }
			if (isset($fields['summary'])) { $options[] = "summary='$fields[summary]'"; }
			if (isset($fields['description'])) { $options[] = "description='$fields[description]'"; }
			if (isset($fields['calendar_id'])) { $options[] = "calendar_id='$fields[calendar_id]'"; }
			if (isset($fields['location_id'])) { $options[] = "location_id='$fields[location_id]'"; }
			if (isset($fields['user_id'])) { $options[] = "user_id='$fields[user_id]'"; }

			# Find events by dates
			if (isset($fields['rangeStart']))
			{
				if (isset($fields['rangeEnd']))
				{
					# Find all the events that could possibly have recurrences inside the range
					$options[] = "((startDate between '$fields[rangeStart]' and '$fields[rangeEnd]')
									or (endDate between '$fields[rangeStart]' and '$fields[rangeEnd]')
									or (startDate<='$fields[rangeStart]' and endDate>='$fields[rangeStart]'))";
				}
				else
				{
					# Just find the events that happen on $rangeStart {Date}
					$options[] = "startDate='$fields[rangeStart]'";
				}
			}

			# Finding on fields from other tables required joining those tables.
			# You can add fields from other tables to $options by adding the join SQL
			# to $this->joins here

			$this->populateList($options);
		}


		protected function loadResult($key) { return new Event($this->list[$key]); }
	}
?>