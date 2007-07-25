<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
	class FacetList extends PDOResultIterator
	{
		public function __construct($fields=null)
		{
			$this->select = 'select facets.id as id from facets';
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
			if (isset($fields['facetGroup_id'])) { $options[] = "facetGroup_id='$fields[facetGroup_id]'"; }
			if (isset($fields['description'])) { $options[] = "description='$fields[description]'"; }


			# Finding on fields from other tables required joining those tables.
			# You can add fields from other tables to $options by adding the join SQL
			# to $this->joins here

			/**
			 * Passing in facet_id should trigger the SQL for relatedFacets
			 */
			if (isset($fields['facet_id']))
			{
				$this->select = 'select distinct(g.facet_id) as id from facets f';
				$this->joins.= ' left join document_facets d on f.id=facet_id';
				$this->joins.= ' left join document_facets g on d.document_id=g.document_id';
				$options[] = "f.id='$fields[facet_id]'";
				$options[] = "g.facet_id!='$fields[facet_id]'";
			}

			if (isset($fields['document_id']))
			{
				$this->joins.= ' left join document_facets on id=facet_id';
				$options[] = "document_id='$fields[document_id]'";
			}

			$this->populateList($options);
		}

		protected function loadResult($key) { return new Facet($this->list[$key]); }
	}
?>