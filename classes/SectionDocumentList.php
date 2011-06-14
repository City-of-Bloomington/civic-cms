<?php
/**
 * @copyright Copyright (C) 2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
class SectionDocumentList extends PDOResultIterator
{
	public function __construct($fields=null)
	{
		$this->select = 'select sectionDocuments.id as id from sectionDocuments';
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
		if (isset($fields['section_id']))
		{
			$options[] = 'section_id=:section_id';
			$parameters[':section_id'] = $fields['section_id'];
		}
		if (isset($fields['document_id']))
		{
			$options[] = 'document_id=:document_id';
			$parameters[':document_id'] = $fields['document_id'];
		}
		if (isset($fields['featured']))
		{
			$options[] = 'featured=:featured';
			$parameters[':featured'] = $fields['featured'];
		}


		# Finding on fields from other tables required joining those tables.
		# You can add fields from other tables to $options by adding the join SQL
		# to $this->joins here
		if ($sort=='title')
		{
			$this->joins = ' left join documents on document_id=document.id';
		}

		$this->populateList($options,$parameters);
	}

	protected function loadResult($key) { return new SectionDocument($this->list[$key]); }
}
