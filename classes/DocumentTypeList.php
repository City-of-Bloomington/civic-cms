<?php
/**
 * @copyright Copyright (C) 2006-2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
class DocumentTypeList extends PDOResultIterator
{

	public function __construct($fields=null)
	{
		$this->select = 'select documentTypes.id as id from documentTypes';
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
		if (isset($fields['type']))
		{
			$options[] = 'type=:type';
			$parameters[':type'] = $fields['type'];
		}
		if (isset($fields['template']))
		{
			$options[] = 'template=:template';
			$parameters[':template'] = $fields['template'];
		}
		if (isset($fields['ordering']))
		{
			$options[] = 'ordering=:ordering';
			$parameters[':ordering'] = $fields['ordering'];
		}
		if (isset($fields['defaultFacetGroup_id']))
		{
			$options[] = 'defaultFacetGroup_id=:defaultFacetGroup_id';
			$parameters[':defaultFacetGroup_id'] = $fields['defaultFacetGroup_id'];
		}
		if (isset($fields['documentInfoFields']))
		{
			$options[] = 'documentInfoFields=:documentInfoFields';
			$parameters[':documentInfoFields'] = $fields['documentInfoFields'];
		}
		if (isset($fields['media_id']))
		{
			$options[] = 'media_id=:media_id';
			$parameters[':media_id'] = $fields['media_id'];
		}
		if (isset($fields['seperateInSearch']))
		{
			$options[] = 'seperateInSearch=:seperateInSearch';
			$parameters[':seperateInSearch'] = $fields['seperateInSearch'];
		}


		# Finding on fields from other tables required joining those tables.
		# You can add fields from other tables to $options by adding the join SQL
		# to $this->joins here

		$this->populateList($options,$parameters);
	}


	protected function loadResult($key) { return new DocumentType($this->list[$key]); }
}
