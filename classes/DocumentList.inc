<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
	class DocumentList extends PDOResultIterator
	{
		public function __construct($fields=null,$sort="id")
		{
			$this->select = "select documents.id from documents";
			$this->sort = $sort;
			if (is_array($fields)) $this->find($fields);
		}


		public function find($fields=null,$sort="id")
		{
			$this->sort = $sort;

			$options = array();
			if (isset($fields['id'])) { $options[] = "id='$fields[id]'"; }
			if (isset($fields['dateTimeCreated'])) { $options[] = "dateTimeCreated='$fields[dateTimeCreated]'"; }
			if (isset($fields['department_id'])) { $options[] = "department_id='$fields[department_id]'"; }


			# Finding on fields from other tables required joining those tables.
			# You can add fields from other tables to $options by adding the join SQL
			# to $this->joins here
			if (isset($fields['section_id']))
			{
				$this->joins.= " left join document_sections on documents.id=document_id";
				$options[] = "section_id='$fields[section_id]'";
			}

			$this->populateList($options);
		}


		protected function loadResult($key) { return new Document($this->list[$key]); }
	}
?>