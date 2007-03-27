<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
	class FacetList extends PDOResultIterator
	{

		public function __construct($fields=null,$sort=null,$limit=null,$groupBy=null)
		{
			$this->select = "select facets.id as id from facets";
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
			if (isset($fields['id'])) { $options[] = "id='$fields[id]'"; }
			if (isset($fields['name'])) { $options[] = "name='$fields[name]'"; }


			# Finding on fields from other tables required joining those tables.
			# You can add fields from other tables to $options by adding the join SQL
			# to $this->joins here
			if (isset($fields['section_id']))
			{
				$this->joins.= " left join section_facets s on facets.id=s.facet_id";
				$options[] = "section_id='$fields[section_id]'";
			}

			if (isset($fields['document_id']))
			{
				$this->joins.= " left join document_facets d on facets.id=d.facet_id";
				$options[] = "document_id='$fields[document_id]'";
			}

			$this->populateList($options);
		}


		protected function loadResult($key) { return new Facet($this->list[$key]); }
	}
?>