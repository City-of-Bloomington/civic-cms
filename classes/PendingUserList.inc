<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
class PendingUserList extends PDOResultIterator
{

	public function __construct($fields=null)
	{
		$this->select = 'select pendingUsers.id as id from pendingUsers';
		if (is_array($fields)) $this->find($fields);
	}

	public function find($fields=null,$sort='id',$limit=null,$groupBy=null)
	{
		$this->sort = $sort;
		$this->limit = $limit;
		$this->groupBy = $groupBy;

		$options = array();
		if (isset($fields['id'])) { $options[] = "id='$fields[id]'"; }
		if (isset($fields['email'])) { $options[] = "email='$fields[email]'"; }
		if (isset($fields['password'])) { $options[] = "password='$fields[password]'"; }
		if (isset($fields['date'])) { $options[] = "date='$fields[date]'"; }


		# Finding on fields from other tables required joining those tables.
		# You can add fields from other tables to $options by adding the join SQL
		# to $this->joins here
		if (isset($fields['hash']))
		{
			$options[] = "md5(concat(id,email,password))='$fields[hash]'";
		}

		$this->populateList($options);
	}

	protected function loadResult($key) { return new PendingUser($this->list[$key]); }
}
