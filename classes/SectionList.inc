<?php
/**
 * @copyright Copyright (C) 2006-2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
class SectionList extends PDOResultIterator
{
	public function __construct($fields=null)
	{
		$this->select = 'select s.id as id from sections s';
		if (is_array($fields)) $this->find($fields);
	}

	public function find($fields=null,$sort='name',$limit=null,$groupBy=null)
	{
		$this->sort = 's.'.$sort;
		$this->limit = $limit;
		$this->groupBy = $groupBy;
		$this->joins = '';

		$options = array();
		$parameters = array();
		if (isset($fields['id']))
		{
			$options[] = 's.id=:id';
			$parameters[':id'] = $fields['id'];
		}
		if (isset($fields['name']))
		{
			$options[] = 's.name=:name';
			$parameters[':name'] = $fields['name'];
		}
		if (isset($fields['nickname']))
		{
			$options[] = 's.nickname=:nickname';
			$parameters[':nickname'] = $fields['nickname'];
		}
		if (isset($fields['sectionDocument_id']))
		{
			$options[] = 's.sectionDocument_id=:sectionDocument_id';
			$parameters[':sectionDocument_id'] = $fields['sectionDocument_id'];
		}
		if (isset($fields['placement']))
		{
			$options[] = 's.placement=:placement';
			$parameters[':placement'] = $fields['placement'];
		}
		if (isset($fields['highlightSubscription']))
		{
			$options[] = $fields['highlightSubscription'] ? 's.highlightSubscription' : '!s.highlightSubscription';
		}

		# Finding on fields from other tables required joining those tables.
		# You can add fields from other tables to $options by adding the join SQL
		# to $this->joins here
		if (isset($fields['postable_by']))
		{
			if ($fields['postable_by']->hasRole(array('Administrator','Webmaster')))
			{
				# Administrators and webmasters can post to all sections,
				# so there's nothing special to be done here
			}
			elseif ($fields['postable_by']->hasRole('Content Creator'))
			{
				# Content creators can only post to sections that their
				# department owns
				$fields['department_id'] = $fields['postable_by']->getDepartment_id();
			}
			else
			{
				# no one else is allowed to post to sections.  Create an option
				# that will result in returning no sections
				$options[] = "1=0";
			}
		}


		if (isset($fields['department_id']))
		{
			$this->joins.= ' left join section_departments sd on s.id=sd.section_id';
			$options[] = 'department_id=:department_id';
			$parameters[':department_id'] = $fields['department_id'];
		}

		if (isset($fields['parent_id']))
		{
			$this->sort = 'p.placement,s.name';
			$this->joins.= ' left join section_parents p on s.id=p.section_id';
			if ($fields['parent_id']=='null')
			{
				$options[] = 'p.parent_id is null';
			}
			else
			{
				$options[] = 'p.parent_id=:parent_id';
				$parameters[':parent_id'] = $fields['parent_id'];
			}
		}

		/**
		 * Use this field to get a list of all sections that include a certain document
		 */
		if (isset($fields['document_id']))
		{
			$this->joins.= ' left join sectionDocuments d on s.id=d.section_id';
			$options[] = 'd.document_id=:document_id';
			$parameters[':document_id'] = $fields['document_id'];
		}

		/**
		 * Use this field to get a list of all sections that have a certain document
		 * as the Homepage for the Section.
		 * There are many documents in a section, only one of them is the home
		 */
		if (isset($fields['homeDocument_id']))
		{
			$this->joins.= ' left join sectionDocuments home on s.sectionDocument_id=home.id';
			$options[] = 'home.document_id=:homeDocument_id';
			$parameters[':homeDocument_id'] = $fields['homeDocument_id'];
		}

		$this->populateList($options,$parameters);
	}

	protected function loadResult($key) { return new Section($this->list[$key]); }
}
