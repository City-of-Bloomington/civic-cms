<?php
/**
 * @copyright 2007-2009 City of Bloomington, Indiana
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
class FacetGroupList extends PDOResultIterator
{
	public function __construct($fields=null)
	{
		$this->select = 'select distinct g.id as id from facetGroups g';
		if (is_array($fields)) {
			$this->find($fields);
		}
	}

	public function find($fields=null,$sort='g.name',$limit=null,$groupBy=null)
	{
		$this->sort = $sort;
		$this->limit = $limit;
		$this->groupBy = $groupBy;

		$options = array();
		$parameters = array();
		if (isset($fields['id'])) {
			$options[] = 'g.id=:id';
			$parameters[':id'] = $fields['id'];
		}
		if (isset($fields['name'])) {
			$options[] = 'g.name=:name';
			$parameters[':name'] = $fields['name'];
		}

		// Finding on fields from other tables required joining those tables.
		// You can add fields from other tables to $options by adding the join SQL
		// to $this->joins here
		$joins = array();

		if (isset($fields['facet_id'])) {
			$joins['facets'] = 'left join facets f on g.id=f.facetGroup_id';
			$options[] = 'f.id=:facet_id';
			$parameters[':facet_id'] = $fields['facet_id'];
		}

		if (isset($fields['department_id'])) {
			$joins['departments'] = 'left join facetGroup_departments dept on g.id=dept.facetGroup_id';
			$options[] = 'dept.department_id=:department_id';
			$parameters[':department_id'] = $fields['department_id'];
		}

		if (isset($fields['document_id'])) {
			$joins['facets'] = 'left join facets f on g.id=f.facetGroup_id';
			$joins['documents'] = 'left join document_facets doc on f.id=doc.facet_id';
			$options[] = 'doc.document_id=:document_id';
			$parameters[':document_id'] = $fields['document_id'];
		}

		if (isset($fields['location_id'])) {
			$joins['facets'] = 'left join facets f on g.id=f.facetGroup_id';
			$joins['locations'] = 'left join location_facets loc on f.id=loc.facet_id';
			$options[] = 'loc.location_id=:location_id';
			$parameters[':document_id'] = $fields['document_id'];
		}

		$this->joins = implode(' ',$joins);
		$this->populateList($options,$parameters);
	}

	protected function loadResult($key)
	{
		return new FacetGroup($this->list[$key]);
	}
}
