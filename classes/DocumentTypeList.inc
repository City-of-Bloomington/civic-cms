<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
	class DocumentTypeList extends PDOResultIterator
	{

		public function __construct($fields=null,$sort="id")
		{
			$this->select = "select documentTypes.id as id from documentTypes";
			$this->sort = $sort;
			if (is_array($fields)) $this->find($fields);
		}
	

		public function find($fields=null,$sort="id")
		{
			$this->sort = $sort;

			$options = array();
			if (isset($fields['id'])) { $options[] = "id='$fields[id]'"; }
			if (isset($fields['type'])) { $options[] = "type='$fields[type]'"; }
			if (isset($fields['template'])) { $options[] = "template='$fields[template]'"; }


			# Finding on fields from other tables required joining those tables.
			# You can add fields from other tables to $options by adding the join SQL
			# to $this->joins here

			$this->populateList($options);
		}
	

		protected function loadResult($key) { return new DocumentType($this->list[$key]); }
	}
?>