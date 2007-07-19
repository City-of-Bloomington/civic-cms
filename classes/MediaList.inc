<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
	class MediaList extends PDOResultIterator
	{

		public function __construct($fields=null,$sort=null,$limit=null,$groupBy=null)
		{
			$this->select = 'select media.id as id from media';
			if (is_array($fields)||$sort||$limit||$groupBy)
			{
				$this->find($fields,$sort,$limit,$groupBy);
			}
		}


		public function find($fields=null,$sort='id',$limit=null,$groupBy=null)
		{
			$this->sort = $sort;
			$this->limit = $limit;
			$this->groupBy = $groupBy;

			$options = array();
			if (isset($fields['id'])) { $options[] = "id='$fields[id]'"; }
			if (isset($fields['mime_type'])) { $options[] = "mime_type='$fields[mime_type]'"; }
			if (isset($fields['media_type'])) { $options[] = "media_type='$fields[media_type]'"; }
			if (isset($fields['title'])) { $options[] = "title='$fields[title]'"; }
			if (isset($fields['description'])) { $options[] = "description='$fields[description]'"; }
			if (isset($fields['md5'])) { $options[] = "md5='$fields[md5]'"; }
			if (isset($fields['department_id'])) { $options[] = "department_id='$fields[department_id]'"; }
			if (isset($fields['uploaded'])) { $options[] = "uploaded='$fields[uploaded]'"; }
			if (isset($fields['uploadedBy'])) { $options[] = "uploadedBy='$fields[uploadedBy]'"; }

			if (isset($fields['filename']))
			{
				$filename = Media::createValidFilename($fields['filename']);
				$options[] = "filename='$filename'";
			}

			# Finding on fields from other tables required joining those tables.
			# You can add fields from other tables to $options by adding the join SQL
			# to $this->joins here
			if (isset($fields['document_id']))
			{
				$this->joins.= ' left join media_documents d on id=d.media_id';
				$options[] = "d.document_id=$fields[document_id]";
			}

			$this->populateList($options);
		}


		protected function loadResult($key) { return new Media($this->list[$key]); }
	}
?>