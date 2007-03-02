<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
	class SectionList extends PDOResultIterator
	{
		public function __construct($fields=null,$sort=null)
		{
			$this->select = "select s.id from sections s";
			if ($sort) { $this->sort = "s.$sort"; }
			if (is_array($fields)) { $this->find($fields); }
		}


		public function find($fields=null,$sort=null)
		{
			if ($sort) { $this->sort = "s.$sort"; }

			$options = array();
			if (isset($fields['id'])) { $options[] = "id='$fields[id]'"; }
			if (isset($fields['name'])) { $options[] = "name='$fields[name]'"; }

			# Finding on fields from other tables required joining those tables.
			# You can add fields from other tables to $options by adding the join SQL
			# to $this->joins here
			if (isset($fields['department_id']))
			{
				$this->joins.= " left join section_departments sd on s.id=sd.section_id";
				$options[] = "department_id='$fields[department_id]'";
			}

			if (isset($fields['parent_id']))
			{
				$this->joins.= " left join section_parents p on s.id=p.section_id";
				$options[] = $fields['parent_id']=='null' ? "p.parent_id is null" : "p.parent_id=$fields[parent_id]";
			}

			if (isset($fields['document_id']))
			{
				$this->joins.= " left join document_sections d on s.id=d.section_id";
				$options[] = "d.document_id='$fields[document_id]'";
			}

			$this->populateList($options);
		}


		protected function loadResult($key) { return new Section($this->list[$key]); }
	}
?>