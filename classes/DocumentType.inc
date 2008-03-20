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
		private $media_id;

		private $defaultFacetGroup;
		private $documentInfoFields = array();
		private $media;

		/**
		 * This will load all fields in the table as properties of this class.
		 * You may want to replace this with, or add your own extra, custom loading
		 */
		public function __construct($id=null)
		{
			if ($id)
			{
				$PDO = Database::getConnection();
				if (is_numeric($id)) { $sql = 'select * from documentTypes where id=?'; }
				else { $sql = 'select * from documentTypes where type=?'; }

				$query = $PDO->prepare($sql);
				$query->execute(array($id));

				$result = $query->fetchAll(PDO::FETCH_ASSOC);
				if (!count($result)) { throw new Exception('documentTypes/unknownDocumentType'); }

				foreach($result[0] as $field=>$value)
				{
					if ($value)
					{
						# The documentInfoFields need to be unserialized
						if ($field=='documentInfoFields') { $value = unserialize($value); }

						$this->$field = $value;
					}
				}
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
			$fields['documentInfoFields'] = count($this->documentInfoFields) ? serialize($this->documentInfoFields) : null;
			$fields['media_id'] = $this->media_id ? $this->media_id : null;

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
			$PDO = Database::getConnection();

			$sql = "update documentTypes set $preparedFields where id={$this->id}";
			$query = $PDO->prepare($sql);
			$query->execute($values);
		}

		private function insert($values,$preparedFields)
		{
			$PDO = Database::getConnection();

			$sql = "insert documentTypes set $preparedFields";
			$query = $PDO->prepare($sql);
			$query->execute($values);
			$this->id = $PDO->lastInsertID();
		}

		/**
		 * Returns a DocumentList with filtered to just documents of this type
		 * @param array $fields Additional fields to filter the DocumentList on
		 */
		public function getDocuments(array $fields=null)
		{
			if (!$fields) { $fields = array(); }
			$fields['documentType_id'] = $this->id;

			$list = new DocumentList();
			$list->find($fields,$this->ordering);

			return $list;
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
		public function getDocumentInfoFields()
		{
			if (!count($this->documentInfoFields))
			{
				$this->documentInfoFields[] = 'title';
			}
			return $this->documentInfoFields;
		}
		public function getMedia_id() { return $this->media_id; }
		public function getMedia()
		{
			if ($this->media_id)
			{
				if (!$this->media) { $this->media = new Media($this->media_id); }
				return $this->media;
			}
		}


		public function setType($string) { $this->type = trim($string); }
		public function setTemplate($text) { $this->template = $text; }
		public function setOrdering($ordering)
		{
			if (is_array($ordering))
			{
				$string = $ordering['field'].' '.$ordering['direction'];
			}
			else { $string = $ordering; }
			$this->ordering = trim($string);
		}
		public function setDefaultFacetGroup_id($int) { $this->defaultFacetGroup = new FacetGroup($int); $this->defaultFacetGroup_id = $int; }
		public function setDefaultFacetGroup($facetGroup) { $this->defaultFacetGroup_id = $facetGroup->getId(); $this->defaultFacetGroup = $facetGroup; }
		public function setDocumentInfoFields($array)
		{
			if (count($array)) { $this->documentInfoFields = $array; }
		}
		public function setMedia_id($int) { $this->media = new Media($int); $this->media_id = $this->media->getId(); }
		public function setMedia($media) { $this->media_id = $this->media->getId(); $this->media = $media; }
	}
