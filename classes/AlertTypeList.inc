<?php
/**
 * @copyright Copyright (C) 2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
class AlertTypeList extends PDOResultIterator
{
	public function __construct($fields=null)
	{
		$this->select = 'select alertTypes.id as id from alertTypes';
		if (is_array($fields)) $this->find($fields);
	}

	public function find($fields=null,$sort='id',$limit=null,$groupBy=null)
	{
		$this->sort = $sort;
		$this->limit = $limit;
		$this->groupBy = $groupBy;

		$options = array();
		if (isset($fields['id'])) { $options[] = "id='$fields[id]'"; }
		if (isset($fields['name'])) { $options[] = "name='$fields[name]'"; }


		# Finding on fields from other tables required joining those tables.
		# You can add fields from other tables to $options by adding the join SQL
		# to $this->joins here

		$this->populateList($options);
	}

	protected function loadResult($key) { return new AlertType($this->list[$key]); }
}
