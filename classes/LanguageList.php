<?php
/**
 * @copyright Copyright (C) 2006-2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
class LanguageList extends PDOResultIterator
{
	public function __construct($fields=null)
	{
		$this->select = 'select languages.id as id from languages';
		if (is_array($fields)) $this->find($fields);
	}

	public function find($fields=null,$sort='code',$limit=null,$groupBy=null)
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
		if (isset($fields['code']))
		{
			$options[] = 'code=:code';
			$parameters[':code'] = $fields['code'];
		}
		if (isset($fields['english']))
		{
			$options[] = 'english=:english';
			$parameters[':english'] = $fields['english'];
		}
		if (isset($fields['native']))
		{
			$options[] = 'native=:native';
			$parameters[':native'] = $fields['native'];
		}
		if (isset($fields['direction']))
		{
			$options[] = 'direction=:direction';
			$parameters[':direction'] = $fields['direction'];
		}


		# Finding on fields from other tables required joining those tables.
		# You can add fields from other tables to $options by adding the join SQL
		# to $this->joins here

		$this->populateList($options,$parameters);
	}


	protected function loadResult($key) { return new Language($this->list[$key]); }
}
