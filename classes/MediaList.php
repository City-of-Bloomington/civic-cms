<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
class MediaList extends PDOResultIterator
{

	public function __construct($fields=null)
	{
		$this->select = 'select media.id as id from media';
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
		if (isset($fields['filename']))
		{
			$filename = Media::createValidFilename($fields['filename']);
			$options[] = 'filename=:filename';
			$parameters[':filename'] = $filename;
		}
		if (isset($fields['mime_type']))
		{
			$options[] = 'mime_type=:mime_type';
			$parameters[':mime_type'] = $fields['mime_type'];
		}
		if (isset($fields['media_type']))
		{
			$options[] = 'media_type=:media_type';
			$parameters[':media_type'] = $fields['media_type'];
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
		if (isset($fields['md5']))
		{
			$options[] = 'md5=:md5';
			$parameters[':md5'] = $fields['md5'];
		}
		if (isset($fields['department_id']))
		{
			$options[] = 'department_id=:department_id';
			$parameters[':department_id'] = $fields['department_id'];
		}
		if (isset($fields['uploaded']))
		{
			$options[] = 'uploaded=:uploaded';
			$parameters[':uploaded'] = $fields['uploaded'];
		}
		if (isset($fields['user_id']))
		{
			$options[] = 'user_id=:user_id';
			$parameters[':user_id'] = $fields['user_id'];
		}

		# Finding on fields from other tables required joining those tables.
		# You can add fields from other tables to $options by adding the join SQL
		# to $this->joins here
		if (isset($fields['document_id']))
		{
			$this->joins.= ' left join media_documents d on id=d.media_id';
			$options[] = "d.document_id=$fields[document_id]";
			$parameters[':document_id'] = $fields['document_id'];
		}

		$this->populateList($options,$parameters);
	}

	protected function loadResult($key) { return new Media($this->list[$key]); }
}
