<?php
/**
 * @copyright Copyright (C) 2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
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
		$this->joins = '';

		$options = array();
		$parameters = array();
		if (isset($fields['id']))
		{
			$options[] = 'id=:id';
			$parameters[':id'] = $fields['id'];
		}
		if (isset($fields['section_id']))
		{
			$options[] = 'section_id=:section_id';
			$parameters[':section_id'] = $fields['section_id'];
		}
		if (isset($fields['user_id']))
		{
			$options[] = 'user_id=:user_id';
			$parameters[':user_id'] = $fields['user_id'];
		}


		# Finding on fields from other tables required joining those tables.
		# You can add fields from other tables to $options by adding the join SQL
		# to $this->joins here

		$this->populateList($options,$parameters);
	}

	protected function loadResult($key) { return new SectionSubscription($this->list[$key]); }
}
