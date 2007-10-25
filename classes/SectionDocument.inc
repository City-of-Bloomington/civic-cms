<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
	class SectionDocument extends ActiveRecord
	{
		private $id;
		private $section_id;
		private $document_id;
		private $featured;


		private $section;
		private $document;



		/**
		 * This will load all fields in the table as properties of this class.
		 * You may want to replace this with, or add your own extra, custom loading
		 */
		public function __construct($id=null)
		{
			$PDO = Database::getConnection();

			if ($id)
			{
				$sql = 'select * from sectionDocuments where id=?';
				$query = $PDO->prepare($sql);
				$query->execute(array($id));

				$result = $query->fetchAll();
				foreach($result[0] as $field=>$value) { if ($value) $this->$field = $value; }
			}
			else
			{
				# This is where the code goes to generate a new, empty instance.
				# Set any default values for properties that need it here
				$this->featured = 0;
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
			if (!$this->section_id || !$this->document_id) { throw new Exception('missingRequiredFields'); }

			$fields = array();
			$fields['section_id'] = $this->section_id ? $this->section_id : null;
			$fields['document_id'] = $this->document_id ? $this->document_id : null;
			$fields['featured'] = $this->featured ? $this->featured : 0;

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

			$sql = "update sectionDocuments set $preparedFields where id={$this->id}";
			$query = $PDO->prepare($sql);
			$query->execute($values);
		}

		private function insert($values,$preparedFields)
		{
			$PDO = Database::getConnection();

			$sql = "insert sectionDocuments set $preparedFields";
			$query = $PDO->prepare($sql);
			$query->execute($values);

			$this->id = $PDO->lastInsertID();
		}

		public function delete()
		{
			if($this->id)
			{
				if (!$this->isHomepage())
				{
					$PDO = Database::getConnection();
					$query = $PDO->prepare('delete from sectionDocuments where id=?');
					$query->execute(array($this->id));
				}
				else { throw new Exception('documents/sectionHomepage'); }
			}
		}

		public function isHomepage()
		{
			return $this->getSection()->getSectionDocument_id()==$this->id;
		}


		/**
		 * Generic Getters
		 */
		public function getId() { return $this->id; }
		public function getSection_id() { return $this->section_id; }
		public function getDocument_id() { return $this->document_id; }
		public function getFeatured() { return $this->featured; }

		public function getSection()
		{
			if ($this->section_id)
			{
				if (!$this->section) { $this->section = new Section($this->section_id); }
				return $this->section;
			}
			else return null;
		}

		public function getDocument()
		{
			if ($this->document_id)
			{
				if (!$this->document) { $this->document = new Document($this->document_id); }
				return $this->document;
			}
			else return null;
		}

		public function isFeatured() { return $this->getFeatured()==1; }

		/**
		 * Generic Setters
		 */
		public function setSection_id($int) { $this->section = new Section($int); $this->section_id = $int; }
		public function setDocument_id($int) { $this->document = new Document($int); $this->document_id = $int; }
		public function setFeatured($int) { $this->featured = $int==1 ? 1 : 0; }

		public function setSection($section) { $this->section_id = $section->getId(); $this->section = $section; }
		public function setDocument($document) { $this->document_id = $document->getId(); $this->document = $document; }
	}
