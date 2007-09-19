<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
	class TagList extends PDOResultIterator
	{
		public function __construct($fields=null)
		{
			$this->select = 'select tags.id as id from tags';
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
			if (isset($fields['tagGroup_id'])) { $options[] = "tagGroup_id='$fields[tagGroup_id]'"; }
			if (isset($fields['description'])) { $options[] = "description='$fields[description]'"; }


			# Finding on fields from other tables required joining those tables.
			# You can add fields from other tables to $options by adding the join SQL
			# to $this->joins here

			/**
			 * Passing in tag_id should trigger the SQL for relatedTags
			 */
			if (isset($fields['tag_id']))
			{
				$this->select = 'select distinct(g.tag_id) as id from tags f';
				$this->joins.= ' left join document_tags d on f.id=tag_id';
				$this->joins.= ' left join document_tags g on d.document_id=g.document_id';
				$options[] = "f.id='$fields[tag_id]'";
				$options[] = "g.tag_id!='$fields[tag_id]'";
			}

			if (isset($fields['document_id']))
			{
				$this->joins.= ' left join document_tags on id=tag_id';
				$options[] = "document_id='$fields[document_id]'";
			}

			$this->populateList($options);
		}

		protected function loadResult($key) { return new Tag($this->list[$key]); }
	}
?>
