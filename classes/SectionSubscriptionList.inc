<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
class SectionSubscriptionList extends PDOResultIterator
{

	public function __construct($fields=null)
	{
		$this->select = 'select section_subscriptions.id as id from section_subscriptions';
		if (is_array($fields)) $this->find($fields);
	}
	

	public function find($fields=null,$sort='id',$limit=null,$groupBy=null)
	{
		$this->sort = $sort;
		$this->limit = $limit;
		$this->groupBy = $groupBy;

		$options = array();
		if (isset($fields['id'])) { $options[] = "id='$fields[id]'"; }
		if (isset($fields['section_id'])) { $options[] = "section_id='$fields[section_id]'"; }
		if (isset($fields['user_id'])) { $options[] = "user_id='$fields[user_id]'"; }


		# Finding on fields from other tables required joining those tables.
		# You can add fields from other tables to $options by adding the join SQL
		# to $this->joins here

		$this->populateList($options);
	}
	

	protected function loadResult($key) { return new SectionSubscription($this->list[$key]); }
}
