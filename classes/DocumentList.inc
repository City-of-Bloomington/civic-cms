<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
	class DocumentList extends PDOResultIterator
	{
		public function __construct($fields=null)
		{
			$this->select = "select documents.id from documents";
			if (is_array($fields)) { $this->find($fields); }
		}


		public function find($fields=null,$sort="title",$limit=null,$groupBy=null)
		{
			$this->sort = $sort;
			$this->limit = $limit;
			$this->groupBy = $groupBy;

			# Sorting on type needs to join the documentTypes table
			if (preg_match('/type/',$this->sort))
			{
				$this->joins.= ' left join documentTypes t on documentType_id=t.id';
			}

			$options = array();

			if (is_array($fields))
			{
				foreach($fields as $key=>$value)
				{
					if (!is_array($value) && !is_object($value)) { $fields[$key] = addslashes($value); }
				}

				if (isset($fields['id'])) { $options[] = "id='$fields[id]'"; }
				if (isset($fields['title'])) { $options[] = "title='$fields[title]'"; }
				if (isset($fields['wikiTitle'])) { $options[] = "wikiTitle='$fields[wikiTitle]'"; }
				if (isset($fields['alias'])) { $options[] = "alias='$fields[alias]'"; }
				if (isset($fields['feature_title'])) { $options[] = "feature_title='$fields[feature_title]'"; }
				if (isset($fields['created'])) { $options[] = "created='$fields[created]'"; }
				if (isset($fields['createdBy'])) { $options[] = "createdBy='$fields[createdBy]'"; }
				if (isset($fields['modified'])) { $options[] = "modified='$fields[modified]'"; }
				if (isset($fields['modifiedBy'])) { $options[] = "modifiedBy='$fields[modifiedBy]'"; }
				if (isset($fields['publishDate'])) { $options[] = "publishDate='$fields[publishDate]'"; }
				if (isset($fields['retireDate'])) { $options[] = "retireDate='$fields[retireDate]'"; }
				if (isset($fields['department_id'])) { $options[] = "department_id='$fields[department_id]'"; }
				if (isset($fields['documentType_id'])) { $options[] = "documentType_id='$fields[documentType_id]'"; }
				if (isset($fields['description'])) { $options[] = "description='$fields[description]'"; }
				if (isset($fields['lockedBy'])) { $options[] = "lockedBy='$fields[lockedBy]'"; }
				if (isset($fields['enablePHP'])) { $options[] = "enablePHP='$fields[enablePHP]'"; }

				# Provide a way to find out active documents.  Documents are active during the time
				# between their Publish and Retire dates.
				if (isset($fields['active']))
				{
					$options[] = "(publishDate<='$fields[active]' and (retireDate is null or retireDate>'$fields[active]'))";
				}

				if (isset($fields['first_letter']))
				{
					$options[] = "upper(substr(title,1,1))='$fields[first_letter]'";
				}


				# Finding on fields from other tables required joining those tables.
				# You can add fields from other tables to $options by adding the join SQL
				# to $this->joins here
				if (isset($fields['wikiTitle_or_alias']))
				{
					$options[] = "(wikiTitle='$fields[wikiTitle_or_alias]' or alias='$fields[wikiTitle_or_alias]')";
				}

				if (isset($fields['section_id']))
				{
					$this->joins.= ' left join document_sections s on documents.id=s.document_id';
					$options[] = "section_id='$fields[section_id]'";

					if (isset($fields['featured'])) { $options[] = "featured='$fields[featured]'"; }
				}

				if (array_key_exists('tag_id',$fields))
				{
					if (is_array($fields['tag_id']))
					{
						$tag_array = array();
						foreach($fields['tag_id'] as $i=>$tag_id)
						{
							# Build a subquery containing all the tags
							$count = $i+1;
							$table = "t$count";

							$tag = "$table.tag_id=$tag_id";
							$tag_array[] = $tag;

							if ($i==0)
							{
								# Start the subquery
								$subquery = "select $table.document_id from document_tags $table";
							}
							else
							{
								# Keep joining on itself
								$subquery.= " left join document_tags $table on t1.document_id=$table.document_id";
							}
						}
						$tags = implode(' and ',$tag_array);
						$subquery.= " where $tags";
						$options[] = "id in ($subquery)";
					}
					else
					{
						$this->joins.= ' left join document_tags f on documents.id=f.document_id';
						$options[] = $fields['tag_id'] ? "tag_id='$fields[tag_id]'" : 'tag_id is null';
					}
				}

				if (isset($fields['media_id']))
				{
					$this->joins.= ' left join media_documents m on documents.id=m.document_id';
					$options[] = "media_id='$fields[media_id]'";
				}

			}

			$this->populateList($options);
		}


		protected function loadResult($key) { return new Document($this->list[$key]); }
	}
?>
