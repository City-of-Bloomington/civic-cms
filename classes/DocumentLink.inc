<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
	class DocumentLink extends ActiveRecord
	{
		private $id;
		private $document_id;
		private $href;
		private $title;
		private $description;
		private $created;

		private $document;

		/**
		 * This will load all fields in the table as properties of this class.
		 * You may want to replace this with, or add your own extra, custom loading
		 */
		public function __construct($id=null)
		{
			if ($id)
			{
				$PDO = Database::getConnection();
				$sql = 'select * from documentLinks where id=?';
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
			if (!$this->document_id || !$this->href) { throw new Exception('missingRequiredFields'); }
			if (!$this->title) { throw new Exception('missingTitle'); }
			if (!$this->description) { throw new Exception('missingDescription'); }

			$fields = array();
			$fields['document_id'] = $this->document_id;
			$fields['href'] = $this->href;
			$fields['title'] = $this->title;
			$fields['description'] = $this->description;

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

			$sql = "update documentLinks set $preparedFields where id={$this->id}";
			if (false === $query = $PDO->prepare($sql)) { $e = $PDO->errorInfo(); throw new Exception($sql.$e[2]); }
			if (false === $query->execute($values)) { $e = $PDO->errorInfo(); throw new Exception($sql.$e[2]); }
		}

		private function insert($values,$preparedFields)
		{
			$PDO = Database::getConnection();

			$sql = "insert documentLinks set $preparedFields,created=now()";
			if (false === $query = $PDO->prepare($sql)) { $e = $PDO->errorInfo(); throw new Exception($sql.$e[2]); }
			if (false === $query->execute($values)) { $e = $PDO->errorInfo(); throw new Exception($sql.$e[2]); }
			$this->id = $PDO->lastInsertID();
		}

		public function delete()
		{
			if ($this->id)
			{
				$PDO = Database::getConnection();
				$sql = "delete from documentLinks where id={$this->id}";
				if (false === $PDO->exec($sql)) { $e = $PDO->errorInfo(); throw new Exception($sql.$e[2]); }
			}
		}

		/**
		 * Generic Getters
		 */
		public function getId() { return $this->id; }
		public function getDocument_id() { return $this->document_id; }
		public function getHref() { return $this->href; }
		public function getTitle() { return $this->title; }
		public function getDescription() { return $this->description; }
		public function getCreated($format=null)
		{
			if ($format && $this->created!=0) return strftime($format,strtotime($this->created));
			else return $this->created;
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

		/**
		 * Generic Setters
		 */
		public function setDocument_id($int) { $this->document = new Document($int); $this->document_id = $int; }
		public function setHref($string) { $this->href = trim($string); }
		public function setTitle($string) { $this->title = trim($string); }
		public function setDescription($string) { $this->description = trim($string); }

		public function setDocument($document) { $this->document_id = $document->getId(); $this->document = $document; }

	}
?>
