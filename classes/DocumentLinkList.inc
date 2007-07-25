<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
	class DocumentLinkList extends PDOResultIterator
	{

		public function __construct($fields=null)
		{
			$this->select = 'select documentLinks.id as id from documentLinks';
			if (is_array($fields)) $this->find($fields);
		}


		public function find($fields=null,$sort='created desc',$limit=null,$groupBy=null)
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
			if (isset($fields['document_id'])) { $options[] = "document_id='$fields[document_id]'"; }
			if (isset($fields['href'])) { $options[] = "href='$fields[href]'"; }
			if (isset($fields['title'])) { $options[] = "title='$fields[title]'"; }
			if (isset($fields['description'])) { $options[] = "description='$fields[description]'"; }
			if (isset($fields['created'])) { $options[] = "created='$fields[created]'"; }


			# Finding on fields from other tables required joining those tables.
			# You can add fields from other tables to $options by adding the join SQL
			# to $this->joins here
			if (isset($fields['section_id']))
			{
				$this->joins.= " left join document_sections using(document_id)";
				$options[] = "section_id='$fields[section_id]'";
			}

			$this->populateList($options);
		}


		protected function loadResult($key) { return new DocumentLink($this->list[$key]); }
	}
?>