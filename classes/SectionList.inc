<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
	class SectionList extends PDOResultIterator
	{
		public function __construct($fields=null)
		{
			$this->select = "select s.id from sections s";
			if (is_array($fields)) { $this->find($fields); }
		}


		public function find($fields=null,$sort='name',$limit=null,$groupBy=null)
		{
			$this->sort = 's.'.$sort;
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
			if (isset($fields['nickname'])) { $options[] = "nickname='$fields[nickname]'"; }

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
				$this->joins.= " left join section_departments sd on s.id=sd.section_id";
				$options[] = "department_id='$fields[department_id]'";
			}

			if (isset($fields['parent_id']))
			{
				$this->sort = 'p.placement,s.name';
				$this->joins.= " left join section_parents p on s.id=p.section_id";
				$options[] = $fields['parent_id']=='null' ? "p.parent_id is null" : "p.parent_id=$fields[parent_id]";
			}

			if (isset($fields['document_id']))
			{
				$this->joins.= " left join document_sections d on s.id=d.section_id";
				$options[] = "d.document_id='$fields[document_id]'";
			}


			$this->populateList($options);
		}


		protected function loadResult($key) { return new Section($this->list[$key]); }
	}
?>