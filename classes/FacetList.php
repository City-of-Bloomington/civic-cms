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
		$this->select = 'select distinct facets.id as id from facets';
		if (is_array($fields)) $this->find($fields);
	}

	public function find($fields=null,$sort='ordering,name',$limit=null,$groupBy=null)
	{
		$this->sort = $sort;
		$this->limit = $limit;
		$this->groupBy = $groupBy;
		$this->joins = '';

		$options = array();
		$parameters = array();
		if (isset($fields['id']))
		{
			$options[] = 'id=:id';
			$parameters[':id'] = $fields['id'];
		}
		if (isset($fields['name']))
		{
			$options[] = 'name=:name';
			$parameters[':name'] = $fields['name'];
		}
		if (isset($fields['facetGroup_id']))
		{
			$options[] = 'facetGroup_id=:facetGroup_id';
			$parameters[':facetGroup_id'] = $fields['facetGroup_id'];
		}
		if (isset($fields['description']))
		{
			$options[] = 'description=:description';
			$parameters[':description'] = $fields['description'];
		}
		if (isset($fields['ordering']))
		{
			$options[] = 'ordering=:ordering';
			$parameters[':ordering'] = $fields['ordering'];
		}


		# Finding on fields from other tables required joining those tables.
		# You can add fields from other tables to $options by adding the join SQL
		# to $this->joins here
		/**
		 * If you want a set of related facets, pass in the documentList
		 * from a facet
		 */
		if (isset($fields['documentList']))
		{
			$documents = $fields['documentList']->getSQL();

			$this->joins.= ' join document_facets df on facets.id=df.facet_id';
			$this->joins.= " join ($documents)related_documents on df.document_id=related_documents.id";

			$parameters = array_merge($parameters,$fields['documentList']->getParameters());
		}

		if (isset($fields['document_id']))
		{
			$this->joins.= ' left join document_facets on id=facet_id';
			$options[] = 'document_id=:document_id';
			$parameters[':document_id'] = $fields['document_id'];
		}

		$this->populateList($options,$parameters);
	}

	protected function loadResult($key) { return new Facet($this->list[$key]); }
}
