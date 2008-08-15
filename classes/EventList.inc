<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
class EventList extends PDOResultIterator
{
	public function __construct($fields=null)
	{
		$this->select = 'select e.id as id from events e';
		if (is_array($fields)) $this->find($fields);
	}

	public function find($fields=null,$sort='id',$limit=null,$groupBy=null)
	{
		$this->sort = $sort;
		$this->limit = $limit;
		$this->groupBy = $groupBy;
		$this->joins = '';

		$options = array();
		$parameters = array();
		if (isset($fields['id']))
		{
			$options[] = 'e.id=:id';
			$parameters[':id'] = $fields['id'];
		}
		if (isset($fields['start']))
		{
			$options[] = 'e.start=:start';
			$parameters[':start'] = $fields['start'];
		}
		if (isset($fields['end']))
		{
			$options[] = 'e.end=:end';
			$parameters[':end'] = $fields['end'];
		}
		if (isset($fields['created']))
		{
			$options[] = 'e.created=:created';
			$parameters[':created'] = $fields['created'];
		}
		if (isset($fields['modified']))
		{
			$options[] = 'e.modified=:modified';
			$parameters[':modified'] = $fields['modified'];
		}
		if (isset($fields['title']))
		{
			$options[] = 'e.title=:title';
			$parameters[':title'] = $fields['title'];
		}
		if (isset($fields['description']))
		{
			$options[] = 'e.description=:description';
			$parameters[':description'] = $fields['description'];
		}
		if (isset($fields['allDayEvent']))
		{
			$options[] = 'e.allDayEvent=:allDayEvent';
			$parameters[':allDayEvent'] = $fields['allDayEvent'];
		}
		if (isset($fields['rrule_freq']))
		{
			$options[] = 'e.rrule_freq=:rrule_freq';
			$parameters[':rrule_freq'] = $fields['rrule_freq'];
		}
		if (isset($fields['rrule_until']))
		{
			$options[] = 'e.rrule_until=:rrule_until';
			$parameters[':rrule_until'] = $fields['rrule_until'];
		}
		if (isset($fields['rrule_count']))
		{
			$options[] = 'e.rrule_count=:rrule_count';
			$parameters[':rrule_count'] = $fields['rrule_count'];
		}
		if (isset($fields['rrule_interval']))
		{
			$options[] = 'e.rrule_interval=:rrule_interval';
			$parameters[':rrule_interval'] = $fields['rrule_interval'];
		}
		if (isset($fields['rrule_byday']))
		{
			$options[] = 'e.rrule_byday=:rrule_byday';
			$parameters[':rrule_byday'] = $fields['rrule_byday'];
		}
		if (isset($fields['rrule_bymonthday']))
		{
			$options[] = 'e.rrule_bymonthday=:rrule_bymonthday';
			$parameters[':rrule_bymonthday'] = $fields['rrule_bymonthday'];
		}
		if (isset($fields['rrule_bysetpos']))
		{
			$options[] = 'e.rrule_bysetpos=:rrule_bysetpos';
			$parameters[':rrule_bysetpos'] = $fields['rrule_bysetpos'];
		}
		if (isset($fields['calendar_id']))
		{
			$options[] = 'e.calendar_id=:calendar_id';
			$parameters[':calendar_id'] = $fields['calendar_id'];
		}
		if (isset($fields['location_id']))
		{
			$options[] = 'e.location_id=:location_id';
			$parameters[':location_id'] = $fields['location_id'];
		}
		if (isset($fields['user_id']))
		{
			$options[] = 'e.user_id=:user_id';
			$parameters[':user_id'] = $fields['user_id'];
		}
		if (isset($fields['contact_name']))
		{
			$options[] = 'e.contact_name=:contact_name';
			$parameters[':contact_name'] = $fields['contact_name'];
		}
		if (isset($fields['contact_phone']))
		{
			$options[] = 'e.contact_phone=:contact_phone';
			$parameters[':contact_phone'] = $fields['contact_phone'];
		}
		if (isset($fields['contact_email']))
		{
			$options[] = 'e.contact_email=:contact_email';
			$parameters[':contact_email'] = $fields['contact_email'];
		}

		# Find events by dates
		if (isset($fields['rangeStart']))
		{
			if (isset($fields['rangeEnd']))
			{
				# Find all the events that could possibly have recurrences inside the range
				$options[] = "(((e.start between from_unixtime($fields[rangeStart]) and from_unixtime($fields[rangeEnd]) ||
							((e.rrule_until is null && e.end between from_unixtime($fields[rangeStart]) and from_unixtime($fields[rangeEnd])) ||
							(e.rrule_until between from_unixtime($fields[rangeStart]) and from_unixtime($fields[rangeEnd])))) ||
							((e.rrule_until is null && from_unixtime($fields[rangeStart]) between e.start and e.end) ||
							(from_unixtime($fields[rangeStart]) between e.start and e.rrule_until)))
							|| (rrule_freq is not null and rrule_until is null and start < from_unixtime($fields[rangeEnd])))";
			}
			else
			{
				# Find the recurrences that end after the given rangeStart
				$options[] = "((e.rrule_until is null && e.end > from_unixtime($fields[rangeStart])) ||
							(e.rrule_until > from_unixtime($fields[rangeStart])))";

			}
		}
		# Finding on fields from other tables required joining those tables.
		# You can add fields from other tables to $options by adding the join SQL
		# to $this->joins here
		if (isset($fields['section_id']))
		{
			$this->joins.= ' left join event_sections s on e.id=s.event_id';
			if (is_array($fields['section_id']))
			{
				$sections = implode(',',$fields['section_id']);
				$options[] = "s.section_id in ($sections)";
			}
			else
			{
				$options[] = 's.section_id=:section_id';
				$parameters[':section_id'] = $fields['section_id'];
			}
		}

		$this->populateList($options,$parameters);
	}

	protected function loadResult($key) { return new Event($this->list[$key]); }
}
