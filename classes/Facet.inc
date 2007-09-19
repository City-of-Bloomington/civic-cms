<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
	class Tag extends ActiveRecord
	{
		private $id;
		private $name;
		private $tagGroup_id;
		private $description;

		private $tagGroup;
		private $documents;

		/**
		 * This will load all fields in the table as properties of this class.
		 * You may want to replace this with, or add your own extra, custom loading
		 */
		public function __construct($id=null)
		{
			global $PDO;

			if ($id)
			{
				$sql = "select * from tags where id=?";
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
			if (!$this->name) { throw new Exception('missingName'); }
			if (!$this->tagGroup_id) { throw new Exception('tags/missingGroup'); }

			$fields = array();
			$fields['name'] = $this->name;
			$fields['tagGroup_id'] = $this->tagGroup_id;
			$fields['description'] = $this->description ? $this->description : null;

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

			$sql = "update tags set $preparedFields where id={$this->id}";
			if (false === $query = $PDO->prepare($sql)) { $e = $PDO->errorInfo(); throw new Exception($sql.$e[2]); }
			if (false === $query->execute($values)) { $e = $PDO->errorInfo(); throw new Exception($sql.$e[2]); }
		}

		private function insert($values,$preparedFields)
		{
			global $PDO;

			$sql = "insert tags set $preparedFields";
			if (false === $query = $PDO->prepare($sql)) { $e = $PDO->errorInfo(); throw new Exception($sql.$e[2]); }
			if (false === $query->execute($values)) { $e = $PDO->errorInfo(); throw new Exception($sql.$e[2]); }
			$this->id = $PDO->lastInsertID();
		}

		public function __toString() { return $this->name; }

		public function delete()
		{
			global $PDO;
			if ($this->id)
			{
				$sql = "delete from document_tags where tag_id={$this->id}";
				if (false === $PDO->exec($sql)) { $e = $PDO->errorInfo(); throw new Exception($sql.$e[2]); }

				$sql = "delete from tags where id={$this->id}";
				if (false === $PDO->exec($sql)) { $e = $PDO->errorInfo(); throw new Exception($sql.$e[2]); }
			}
		}
		public function hasGroup($group) { return in_array($group->getId(),array_keys($this->getGroups())); }


		/**
		 * Tags are related to each other if they both have the same documents
		 */
		public function getRelatedTags()
		{
			return new TagList(array('tag_id'=>$this->id));
		}

		public function getRelatedGroups()
		{
			return $this->getTagGroup()->getRelatedGroups();
		}

		public function getId() { return $this->id; }
		public function getName() { return $this->name; }
		public function getTagGroup_id() { return $this->tagGroup_id; }
		public function getDescription() { return $this->description; }
		public function getTagGroup()
		{
			if ($this->tagGroup_id)
			{
				if (!$this->tagGroup) { $this->tagGroup = new TagGroup($this->tagGroup_id); }
				return $this->tagGroup;
			}
			else return null;
		}

		/**
		 * @param array $fields
		 *  Pass in an array of extra fields used to populate the DocumentList
		 */
		public function getDocuments($fields=null)
		{
			if (!is_array($fields)) { $fields = array(); }
			$fields['tag_id'] = $this->id;
			$fields['active'] = date('Y-m-d');

			if (!$this->documents) { $this->documents = new DocumentList($fields); }
			return $this->documents;
		}

		public function setName($string) { $this->name = trim($string); }
		public function setTagGroup_id($int) { $this->tagGroup = new TagGroup($int); $this->tagGroup_id = $int; }
		public function setDescription($string) { $this->description = trim($string); }
		public function setTagGroup($tagGroup) { $this->tagGroup_id = $tagGroup->getId(); $this->tagGroup = $tagGroup; }
	}
?>
