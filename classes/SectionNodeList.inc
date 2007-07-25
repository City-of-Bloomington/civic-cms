<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
	class SectionNodeList extends PDOResultIterator
	{
		public function __construct($fields=null,$sort='placement')
		{
			$this->select = 'select section_parents.id as id from section_parents';
			$this->sort = $sort;
			if (is_array($fields)) $this->find($fields);
		}


		public function find($fields=null,$sort='placement',$limit=null,$groupBy=null)
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
			if (isset($fields['section_id'])) { $options[] = "section_id='$fields[section_id]'"; }
			if (isset($fields['parent_id'])) { $options[] = "parent_id='$fields[parent_id]'"; }
			if (isset($fields['placement'])) { $options[] = "placement='$fields[placement]'"; }


			# Finding on fields from other tables required joining those tables.
			# You can add fields from other tables to $options by adding the join SQL
			# to $this->joins here

			$this->populateList($options);
		}


		protected function loadResult($key) { return new SectionNode($this->list[$key]); }
	}
?>