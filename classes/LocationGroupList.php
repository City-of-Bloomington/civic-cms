<?php
/**
 * @copyright 2007-2009 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
class LocationGroupList extends PDOResultIterator
{
	public function __construct($fields=null)
	{
		$this->select = 'select locationGroups.id as id from locationGroups';
		if (is_array($fields)) $this->find($fields);
	}

	public function find($fields=null,$sort='name',$limit=null,$groupBy=null)
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
		if (isset($fields['name']))
		{
			$options[] = 'name=:name';
			$parameters[':name'] = $fields['name'];
		}
		if (isset($fields['department_id']))
		{
			$options[] = 'department_id=:department_id';
			$parameters[':department_id'] = $fields['department_id'];
		}
		if (isset($fields['description']))
		{
			$options[] = 'description=:description';
			$parameters[':description'] = $fields['description'];
		}
		if (isset($fields['default'])) {
			$default = $fields['default'] ? 1 : 0;
			$options[] = 'defaultFlag=:defaultFlag';
			$parameters[':defaultFlag'] = $default;
		}


		# Finding on fields from other tables required joining those tables.
		# You can add fields from other tables to $options by adding the join SQL
		# to $this->joins here
		if (isset($fields['location_id']))
		{
			$this->joins.= ' left join locationGroup_locations on id=locationGroup_id';
			$options[] = 'location_id=:location_id';
			$parameters[':location_id'] = $fields['location_id'];
		}

		$this->populateList($options,$parameters);
	}

	protected function loadResult($key) { return new LocationGroup($this->list[$key]); }
}
