<?php
/**
 * @copyright Copyright (C) 2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 */
class CalendarList extends PDOResultIterator
{

	public function __construct($fields=null)
	{
		$this->select = 'select calendars.id as id from calendars';
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
			$options[] = "id=:id";
			$parameters[':id'] = $fields['id'];
		}
		if (isset($fields['name']))
		{
			$options[] = "name=:name";
			$parameters[':name'] = $fields['name'];
		}
		if (isset($fields['description']))
		{
			$options[] = "description=:description";
			$parameters[':description'] = $fields['description'];
		}
		if (isset($fields['user_id']))
		{
			$options[] = "user_id=:user_id";
			$parameters[':user_id'] = $fields['user_id'];
		}


		# Finding on fields from other tables required joining those tables.
		# You can add fields from other tables to $options by adding the join SQL
		# to $this->joins here

		$this->populateList($options,$parameters);
	}


	protected function loadResult($key) { return new Calendar($this->list[$key]); }
}
