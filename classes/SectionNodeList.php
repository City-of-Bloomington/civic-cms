<?php
/**
 * @copyright Copyright (C) 2007-2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
class SectionNodeList extends PDOResultIterator
{
	public function __construct($fields=null)
	{
		$this->select = 'select section_parents.id as id from section_parents';
		if (is_array($fields)) $this->find($fields);
	}

	public function find($fields=null,$sort='placement',$limit=null,$groupBy=null)
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
		if (isset($fields['parent_id']))
		{
			$options[] = 'parent_id=:parent_id';
			$parameters[':parent_id'] = $fields['parent_id'];
		}
		if (isset($fields['placement']))
		{
			$options[] = 'placement=:placement';
			$parameters[':placement'] = $fields['placement'];
		}

		# Finding on fields from other tables required joining those tables.
		# You can add fields from other tables to $options by adding the join SQL
		# to $this->joins here

		$this->populateList($options,$parameters);
	}

	protected function loadResult($key) { return new SectionNode($this->list[$key]); }
}
