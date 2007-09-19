<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
	class TagGroupList extends PDOResultIterator
	{
		public function __construct($fields=null)
		{
			$this->select = 'select tagGroups.id as id from tagGroups';
			if (is_array($fields)) $this->find($fields);
		}


		public function find($fields=null,$sort='name',$limit=null,$groupBy=null)
		{
			$this->sort = $sort;
			$this->limit = $limit;
			$this->groupBy = $groupBy;

			if (is_array($fields))
			{
				foreach($fields as $key=>$value)
				{
					if (!is_array($value) && !is_object($value)) { $fields[$key] = addslashes($value); }
				}
			}

			$options = array();
			if (isset($fields['id'])) { $options[] = "id='$fields[id]'"; }
			if (isset($fields['name'])) { $options[] = "name='$fields[name]'"; }


			# Finding on fields from other tables required joining those tables.
			# You can add fields from other tables to $options by adding the join SQL
			# to $this->joins here
			if (isset($fields['tag_id']))
			{
				$this->joins.= ' left join tagGroup_tags f on id=f.tagGroup_id';
				$options[] = "f.tag_id='$fields[tag_id]'";
			}

			if (isset($fields['department_id']))
			{
				$this->joins.= ' left join tagGroup_departments d on id=d.tagGroup_id';
				$options[] = "d.department_id='$fields[department_id]'";
			}

			$this->populateList($options);
		}

		protected function loadResult($key) { return new TagGroup($this->list[$key]); }
	}
?>
