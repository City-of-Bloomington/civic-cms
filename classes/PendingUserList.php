<?php
/**
 * @copyright Copyright (C) 2007-2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
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
		$this->joins = '';

		$options = array();
		$parameters = array();
		if (isset($fields['id']))
		{
			$options[] = 'id=:id';
			$parameters[':id'] = $fields['id'];
		}
		if (isset($fields['email']))
		{
			$options[] = 'email=:email';
			$parameters[':email'] = $fields['email'];
		}
		if (isset($fields['password']))
		{
			$options[] = 'password=:password';
			$parameters[':password'] = $fields['password'];
		}
		if (isset($fields['date']))
		{
			$options[] = 'date=:date';
			$parameters[':date'] = $fields['date'];
		}

		# Finding on fields from other tables required joining those tables.
		# You can add fields from other tables to $options by adding the join SQL
		# to $this->joins here
		if (isset($fields['hash']))
		{
			$options[] = 'md5(concat(id,email,password))=:hash';
			$parameters[':hash'] = $fields['hash'];
		}

		$this->populateList($options);
	}

	protected function loadResult($key) { return new PendingUser($this->list[$key]); }
}
