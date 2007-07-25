<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
	class LanguageList extends PDOResultIterator
	{

		public function __construct($fields=null,$sort=null,$limit=null,$groupBy=null)
		{
			$this->select = "select languages.code as id from languages";
			if (is_array($fields)||$sort||$limit||$groupBy)
			{
				$this->find($fields,$sort,$limit,$groupBy);
			}
		}


		public function find($fields=null,$sort="code",$limit=null,$groupBy=null)
		{
			$this->sort = $sort;
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
			if (isset($fields['code'])) { $options[] = "code='$fields[code]'"; }
			if (isset($fields['english'])) { $options[] = "english='$fields[english]'"; }
			if (isset($fields['native'])) { $options[] = "native='$fields[native]'"; }


			# Finding on fields from other tables required joining those tables.
			# You can add fields from other tables to $options by adding the join SQL
			# to $this->joins here

			$this->populateList($options);
		}


		protected function loadResult($key) { return new Language($this->list[$key]); }
	}
?>