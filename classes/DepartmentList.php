<?php
/**
 * @copyright Copyright (C) 2006-2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
class DepartmentList extends PDOResultIterator
{

	public function __construct($fields=null)
	{
		$this->select = 'select departments.id as id from departments';
		if (is_array($fields)) $this->find($fields);
	}


	public function find($fields=null,$sort='name',$limit=null,$groupBy=null)
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
		if (isset($fields['address1']))
		{
			$options[] = 'address1=:address1';
			$parameters[':address1'] = $fields['address1'];
		}
		if (isset($fields['address2']))
		{
			$options[] = 'address2=:address2';
			$parameters[':address2'] = $fields['address2'];
		}
		if (isset($fields['city']))
		{
			$options[] = 'city=:city';
			$parameters[':city'] = $fields['city'];
		}
		if (isset($fields['state']))
		{
			$options[] = 'state=:state';
			$parameters[':state'] = $fields['state'];
		}
		if (isset($fields['zip']))
		{
			$options[] = 'zip=:zip';
			$parameters[':zip'] = $fields['zip'];
		}
		if (isset($fields['phone']))
		{
			$options[] = 'phone=:phone';
			$parameters[':phone'] = $fields['phone'];
		}
		if (isset($fields['email']))
		{
			$options[] = 'email=:email';
			$parameters[':email'] = $fields['email'];
		}
		if (isset($fields['ldap_name']))
		{
			$options[] = 'ldap_name=:ldap_name';
			$parameters[':ldap_name'] = $fields['ldap_name'];
		}
		if (isset($fields['document_id']))
		{
			$options[] = 'document_id=:document_id';
			$parameters[':document_id'] = $fields['document_id'];
		}
		if (isset($fields['location_id']))
		{
			$options[] = 'location_id=:location_id';
			$parameters[':location_id'] = $fields['location_id'];
		}

		if (isset($fields['first_letter']))
		{
			$options[] = 'upper(substr(name,1,1))=:first_letter';
			$parameters[':first_letter'] = $fields['first_letter'];
		}


		# Finding on fields from other tables required joining those tables.
		# You can add fields from other tables to $options by adding the join SQL
		# to $this->joins here
		if (isset($fields['section_id']))
		{
			$this->joins.= ' left join section_departments s on s.department_id=departments.id';
			$options[] = 's.section_id=:section_id';
			$parameters[':section_id'] = $fields['section_id'];
		}

		if (isset($fields['calendar_id']))
		{
			$this->joins.= ' left join calendar_departments c on c.department_id=departments.id';
			$options[] = 'c.calendar_id=:calendar_id';
			$parameters[':calendar_id'] = $fields['calendar_id'];
		}

		if (isset($fields['facetGroup_id']))
		{
			$this->joins.= ' left join facetGroup_departments f on f.department_id=departments.id';
			$options[] = 'f.facetGroup_id=:facetGroup_id';
			$parameters[':facetGroup_id'] = $fields['facetGroup_id'];
		}

		$this->populateList($options,$parameters);
	}


	protected function loadResult($key) { return new Department($this->list[$key]); }
}
