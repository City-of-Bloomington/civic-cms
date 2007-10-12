<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
	class SectionDocumentList extends PDOResultIterator
	{

		public function __construct($fields=null)
		{
			$this->select = 'select sectionDocuments.id as id from sectionDocuments';
			if (is_array($fields)) $this->find($fields);
		}


		public function find($fields=null,$sort='id',$limit=null,$groupBy=null)
		{
			$this->sort = $sort;
			$this->limit = $limit;
			$this->groupBy = $groupBy;

			$options = array();
			if (isset($fields['id'])) { $options[] = "id='$fields[id]'"; }
			if (isset($fields['document_id'])) { $options[] = "document_id='$fields[document_id]'"; }
			if (isset($fields['section_id'])) { $options[] = "section_id='$fields[section_id]'"; }
			if (isset($fields['featured'])) { $options[] = "featured='$fields[featured]'"; }


			# Finding on fields from other tables required joining those tables.
			# You can add fields from other tables to $options by adding the join SQL
			# to $this->joins here
			if ($sort=='title')
			{
				$this->joins = ' left join documents on document_id=document.id';
			}

			$this->populateList($options);
		}


		protected function loadResult($key) { return new SectionDocument($this->list[$key]); }
	}
