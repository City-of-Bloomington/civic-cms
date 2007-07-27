<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
	class DocumentList extends PDOResultIterator
	{
		public function __construct($fields=null,$sort=null,$limit=null,$groupBy=null)
		{
			$this->select = "select documents.id from documents";
			if (is_array($fields)||$sort||$limit||$groupBy)
			{
				$this->find($fields,$sort,$limit,$groupBy);
			}
		}


		public function find($fields=null,$sort="id",$limit=null,$groupBy=null)
		{
			$this->sort = $sort;
			$this->limit = $limit;
			$this->groupBy = $groupBy;

			$options = array();

			if (is_array($fields))
			{
				foreach($fields as $key=>$value)
				{
					if (!is_array($value) && !is_object($value)) { $fields[$key] = addslashes($value); }
				}
			}
			if (isset($fields['id'])) { $options[] = "id='$fields[id]'"; }
			if (isset($fields['title'])) { $options[] = "title='$fields[title]'"; }
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


			# Finding on fields from other tables required joining those tables.
			# You can add fields from other tables to $options by adding the join SQL
			# to $this->joins here
			if (isset($fields['title_or_alias']))
			{
				$options[] = "(title='$fields[title_or_alias]' or alias='$fields[title_or_alias]')";
			}

			if (ereg('type',$this->sort))
			{
				# Sorting on type needs to join the documentTypes table
				$this->joins.= ' left join documentTypes t on documentType_id=t.id';
			}
			if (isset($fields['section_id']))
			{
				$this->joins.= ' left join document_sections s on documents.id=s.document_id';
				$options[] = "section_id='$fields[section_id]'";

				if (isset($fields['featured'])) { $options[] = "featured='$fields[featured]'"; }
			}

			if (isset($fields['facet_id']))
			{

				if (is_array($fields['facet_id']))
				{
					$facet_array = array();
					foreach($fields['facet_id'] as $i=>$facet_id)
					{
						# Build a subquery containing all the facets
						$count = $i+1;
						$table = "t$count";

						$facet = "$table.facet_id=$facet_id";
						$facet_array[] = $facet;

						if ($i==0)
						{
							# Start the subquery
							$subquery = "select $table.document_id from document_facets $table";
						}
						else
						{
							# Keep joining on itself
							$subquery.= " left join document_facets $table on t1.document_id=$table.document_id";
						}
					}
					$facets = implode(' and ',$facet_array);
					$subquery.= " where $facets";
					$options[] = "id in ($subquery)";
				}
				else
				{
					$this->joins.= ' left join document_facets f on documents.id=f.document_id';
					$options[] = "facet_id='$fields[facet_id]'";
				}
			}

			if (isset($fields['media_id']))
			{
				$this->joins.= ' left join media_documents m on documents.id=m.document_id';
				$options[] = "media_id='$fields[media_id]'";
			}

			$this->populateList($options);
		}


		protected function loadResult($key) { return new Document($this->list[$key]); }
	}
?>