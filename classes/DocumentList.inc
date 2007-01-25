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
			if (is_array($fields)) $this->find($fields,$sort);
		}


		public function find($fields=null,$sort="id")
		{
			$this->sort = $sort;

			$options = array();
			if (isset($fields['id'])) { $options[] = "id='$fields[id]'"; }
			if (isset($fields['dateTimeCreated'])) { $options[] = "dateTimeCreated='$fields[dateTimeCreated]'"; }
			if (isset($fields['createdBy'])) { $options[] = "createdBy='$fields[createdBy]'"; }
			if (isset($fields['modifiedBy'])) { $options[] = "modifiedBy='$fields[modifiedBy]'"; }
			if (isset($fields['publishDate'])) { $options[] = "publishDate='$fields[publishDate]'"; }
			if (isset($fields['retireDate'])) { $options[] = "retireDate='$fields[retireDate]'"; }
			if (isset($fields['department_id'])) { $options[] = "department_id='$fields[department_id]'"; }


			# Finding on fields from other tables required joining those tables.
			# You can add fields from other tables to $options by adding the join SQL
			# to $this->joins here
			if (isset($fields['section_id']))
			{
				$this->joins.= " left join document_sections s on documents.id=s.document_id";
				$options[] = "section_id='$fields[section_id]'";
			}

			if (isset($fields['facet_id']))
			{
				$this->joins.= " left join document_facets f on documents.id=f.document_id";
				$options[] = "facet_id='$fields[facet_id]'";
			}

			$this->populateList($options);
		}


		protected function loadResult($key) { return new Document($this->list[$key]); }
	}
?>