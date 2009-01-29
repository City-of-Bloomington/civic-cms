<?php
/**
 * @copyright Copyright (C) 2007-2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
class DocumentLinkList extends PDOResultIterator
{

	public function __construct($fields=null)
	{
		$this->select = 'select documentLinks.id as id from documentLinks';
		if (is_array($fields)) $this->find($fields);
	}


	public function find($fields=null,$sort='id',$limit=null,$groupBy=null)
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
		if (isset($fields['document_id']))
		{
			$options[] = 'document_id=:document_id';
			$parameters[':document_id'] = $fields['document_id'];
		}
		if (isset($fields['href']))
		{
			$options[] = 'href=:href';
			$parameters[':href'] = $fields['href'];
		}
		if (isset($fields['title']))
		{
			$options[] = 'title=:title';
			$parameters[':title'] = $fields['title'];
		}
		if (isset($fields['description']))
		{
			$options[] = 'description=:description';
			$parameters[':description'] = $fields['description'];
		}
		if (isset($fields['created']))
		{
			$options[] = 'created=:created';
			$parameters[':created'] = $fields['created'];
		}


		# Finding on fields from other tables required joining those tables.
		# You can add fields from other tables to $options by adding the join SQL
		# to $this->joins here
		if (isset($fields['section_id']))
		{
			$this->joins.= ' left join sectionDocuments using(document_id)';
			$options[] = 'section_id=:section_id';
			$parameters[':section_id'] = $fields['section_id'];
		}

		$this->populateList($options,$parameters);
	}

	protected function loadResult($key) { return new DocumentLink($this->list[$key]); }
}

