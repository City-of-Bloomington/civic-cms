<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
	class DocumentType extends ActiveRecord
	{
		private $id;
		private $type;
		private $template;
		private $ordering;
		private $defaultFacetGroup_id;

		private $document_list;
		private $defaultFacetGroup;

		/**
		 * This will load all fields in the table as properties of this class.
		 * You may want to replace this with, or add your own extra, custom loading
		 */
		public function __construct($id=null)
		{
			global $PDO;

			if ($id)
			{
				if (is_numeric($id)) { $sql = 'select * from documentTypes where id=?'; }
				else { $sql = 'select * from documentTypes where type=?'; }
				try
				{
					$query = $PDO->prepare($sql);
					$query->execute(array($id));
				}
				catch (Exception $e) { throw $e; }

				$result = $query->fetchAll();
				foreach($result[0] as $field=>$value) { if ($value) $this->$field = $value; }
			}
			else
			{
				# This is where the code goes to generate a new, empty instance.
				# Set any default values for properties that need it here
				$this->ordering = 'title';
			}
		}


		/**
		 * This generates generic SQL that should work right away.
		 * You can replace this $fields code with your own custom SQL
		 * for each property of this class,
		 */
		public function save()
		{
			# Check for required fields here.  Throw an exception if anything is missing.

			$fields = array();
			$fields['type'] = $this->type ? $this->type : null;
			$fields['template'] = $this->template ? $this->template : null;
			$fields['ordering'] = $this->ordering ? $this->ordering : null;
			$fields['defaultFacetGroup_id'] = $this->defaultFacetGroup_id ? $this->defaultFacetGroup_id : null;

			# Split the fields up into a preparedFields array and a values array.
			# PDO->execute cannot take an associative array for values, so we have
			# to strip out the keys from $fields
			$preparedFields = array();
			foreach($fields as $key=>$value)
			{
				$preparedFields[] = "$key=?";
				$values[] = $value;
			}
			$preparedFields = implode(",",$preparedFields);


			if ($this->id) { $this->update($values,$preparedFields); }
			else { $this->insert($values,$preparedFields); }
		}

		private function update($values,$preparedFields)
		{
			global $PDO;

			$sql = "update documentTypes set $preparedFields where id={$this->id}";
			if (false === $query = $PDO->prepare($sql)) { $e = $PDO->errorInfo(); throw new Exception($sql.$e[2]); }
			if (false === $query->execute($values)) { $e = $PDO->errorInfo(); throw new Exception($sql.$e[2]); }
		}

		private function insert($values,$preparedFields)
		{
			global $PDO;

			$sql = "insert documentTypes set $preparedFields";
			if (false === $query = $PDO->prepare($sql)) { $e = $PDO->errorInfo(); throw new Exception($sql.$e[2]); }
			if (false === $query->execute($values)) { $e = $PDO->errorInfo(); throw new Exception($sql.$e[2]); }
			$this->id = $PDO->lastInsertID();
		}

		public function getDocuments($sort=null)
		{
			if (!$this->document_list)
			{
				$this->document_list = new DocumentList();
				$this->document_list->find(array('documentType_id'=>$this->id),$sort);
			}
			return $this->document_list;
		}

		public function __toString() { return $this->type; }

		public function getId() { return $this->id; }
		public function getType() { return $this->type; }
		public function getTemplate() { return $this->template; }
		public function getOrdering() { return $this->ordering; }
		public function getDefaultFacetGroup_id() { return $this->defaultFacetGroup_id; }
		public function getDefaultFacetGroup()
		{
			if (!$this->defaultFacetGroup)
			{
				if ($this->defaultFacetGroup_id) { $this->defaultFacetGroup = new FacetGroup($this->defaultFacetGroup_id); }
			}
			return $this->defaultFacetGroup;
		}


		public function setType($string) { $this->type = trim($string); }
		public function setTemplate($text) { $this->template = $text; }
		public function setOrdering($string) { $this->ordering = trim($string); }
		public function setDefaultFacetGroup_id($int) { $this->defaultFacetGroup = new FacetGroup($int); $this->defaultFacetGroup_id = $int; }
		public function setDefaultFacetGroup($facetGroup) { $this->defaultFacetGroup_id = $facetGroup->getId(); $this->defaultFacetGroup = $facetGroup; }
	}
?>