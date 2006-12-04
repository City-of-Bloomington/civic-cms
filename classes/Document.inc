<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
	class Document extends ActiveRecord
	{
		private $id;
		private $title;
		private $created;
		private $modified;
		private $modifiedBy;
		private $department_id;

		private $department;
		private $content;
		private $contentDirectory;

		private $sections;
		private $deletedSectionIds = array();
		private $newSectionIds = array();

		/**
		 * This will load all fields in the table as properties of this class.
		 * You may want to replace this with, or add your own extra, custom loading
		 */
		public function __construct($id=null)
		{
			global $PDO;

			if ($id)
			{
				$sql = "select * from documents where id=?";
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
				$this->modifiedBy = $_SESSION['USER']->getId();
				$this->setDepartment_id($_SESSION['USER']->getDepartment_id());
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
			if (!$this->department_id || !count($this->getSections())) { throw new Exception('missingRequiredFields'); }

			$fields = array();
			$fields['title'] = $this->title;
			$fields['created'] = $this->created ? $this->created : 'now()';
			$fields['modified'] = null;
			$fields['modifiedBy'] = $this->modifiedBy;
			$fields['department_id'] = $this->department_id;

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

			$this->saveSections();
			$this->saveContent();
		}

		private function update($values,$preparedFields)
		{
			global $PDO;

			$sql = "update documents set $preparedFields where id={$this->id}";
			if (false === $query = $PDO->prepare($sql)) { $e = $PDO->errorInfo(); throw new Exception($sql.$e[2]); }
			if (false === $query->execute($values)) { $e = $PDO->errorInfo(); throw new Exception($sql.$e[2]); }
		}

		private function insert($values,$preparedFields)
		{
			global $PDO;

			$sql = "insert documents set $preparedFields";
			if (false === $query = $PDO->prepare($sql)) { $e = $PDO->errorInfo(); throw new Exception($sql.$e[2]); }
			if (false === $query->execute($values)) { $e = $PDO->errorInfo(); throw new Exception($sql.$e[2]); }
			$this->id = $PDO->lastInsertID();

			$sql = "select dateTimeCreated from documents where id=$this->id";
			foreach($PDO->query($sql) as $row) { $this->dateTimeCreated = $row['dateTimeCreated']; }
		}

		private function saveContent()
		{
			$directory = $this->getContentDirectory();
			$file = "$directory/{$this->id}.$_SESSION[LANGUAGE]";

			list($year,$month,$day) = explode("-",$this->getDateCreated());

			$sandbox = new SubversionWorkingCopy(APPLICATION_HOME."/data");
			if (!is_dir($directory))
			{
				mkdir($directory,0775,true);
				$sandbox->add(APPLICATION_HOME."/data/documents/$year","--force");
			}
			file_put_contents($file,$this->getContent());

			$out = $sandbox->status($file);
			if (count($out) && $out[0]{0} == "?") { $sandbox->add($file); }
			$sandbox->commit(APPLICATION_HOME."/data/documents/$year",$_SESSION['USER']->getUsername());


			# Inform the people on the watch list
			foreach($this->getWatches() as $watch) { $watch->notify(); }
		}
		public function getContent()
		{
			# Content won't exist as a file until it's been saved to the database
			# The database will give it an ID and a dateTimeCreated
			if ($this->id)
			{
				if (!$this->content)
				{
					$directory = $this->getContentDirectory();
					# Try to load the preferred language version of the document
					if (file_exists("$directory/{$this->id}.$_SESSION[LANGUAGE]"))
					{
						$this->content = file_get_contents("$directory/{$this->id}.$_SESSION[LANGUAGE]");
					}
					#elseif (file_exists("$directory/{$this->id}.".DEFAULT_LANGUAGE))
					#{
					#	$this->content = file_get_contents("$directory/{$this->id}.".DEFAULT_LANGUAGE);
					#}
				}
			}
			return $this->content;
		}
		private function getContentDirectory()
		{
			if (!$this->contentDirectory)
			{
				list($year,$month,$day) = explode("-",$this->getDateCreated());
				$this->contentDirectory = APPLICATION_HOME."/data/documents/$year/$month/$day";
			}
			return $this->contentDirectory;
		}
		public function getLanguages()
		{
			$languages = array();
			foreach(glob($this->getContentDirectory()."/{$this->id}.*") as $file)
			{
				list($id,$ext) = explode(".",basename($file));
				$languages[] = new Language($ext);
			}
			return $languages;
		}

		private function saveSections()
		{
			global $PDO;

			# Clear out any deleted sections
			if (count($this->deletedSectionIds))
			{
				$sections = implode(",",$this->deletedSectionIds);
				$sql = "delete from document_sections where section_id in ($sections)";
				if (false === $PDO->exec($sql)) { $e = $PDO->errorInfo(); throw new Exception($sql.$e[2]); }
			}

			# Add in any new sections
			if (count($this->newSectionIds))
			{
				$query = $PDO->prepare("insert document_sections values($this->id,?)");
				foreach($this->newSectionIds as $section_id)
				{
					try { $query->execute(array($section_id)); }
					catch (Exception $e) { throw $e; }
				}
			}
		}

		public function addSection($section)
		{
			$this->newSectionIds[] = $section->getId();
			$this->sections[] = $section;
		}


		public function addWatch($user)
		{
			global $PDO;

			$query = $PDO->prepare("insert document_watches values(?,?)");
			$query->execute(array($this->id,$user->getId()));
		}
		public function removeWatch($user)
		{
			global $PDO;

			$query = $PDO->prepare("delete from document_watches where document_id=? and user_id=?");
			$query->execute(array($this->id,$user->getId()));
		}
		public function getWatches()
		{
			global $PDO;

			$watches = array();
			foreach($PDO->query("select * from document_watches where document_id={$this->id}") as $row)
			{
				$watches[] = new Watch($this->id,$row['user_id']);
			}
			return $watches;
		}

		public function getId() { return $this->id; }
		public function getTitle() { return $this->title; }
		public function getCreated() { return $this->created; }
		public function getModified() { return $this->modified; }
		public function getModifiedBy() { return $this->modifiedBy; }
		public function getDepartment_id() { return $this->department_id; }
		public function getDepartment()
		{
			if (!$this->department) { $this->department = new Department($this->department_id); }
			return $this->department;
		}
		public function getSections()
		{
			if (!count($this->sections))
			{
				$this->sections = array();
				foreach(new SectionList(array('document_id'=>$this->id)) as $section)
				{
					$this->sections[$section->getId()] = $section;
				}
			}
			return $this->sections;
		}
		public function getDateCreated()
		{
			list ($dateCreated,$timeCreated) = explode(' ',$this->created);
			return $dateCreated;
		}




		public function setTitle($string) { $this->title = trim($string); }
		public function setContent($string) { $this->content = trim($string); }
		public function setModifiedBy($user) { $this->modifiedBy = $user->getId(); }
		public function setDepartment_id($int) { $this->department = new Department($int); $this->department_id = $int; }
		public function setDepartment($department) { $this->department_id = $department->getId(); $this->department = $department; }
		public function setSections(array $sections)
		{
			# Make sure to call $this->getSections once and only once in this function.
			# We need to have this->sections populated, but we don't want to repopulate it
			# once we start making changes to it.

			# Delete any existing sections that aren't in the new array
			foreach($this->getSections() as $section)
			{
				if (!array_key_exists($section->getId(),$sections))
				{
					$this->deletedSectionIds[] = $section->getId();
					unset($this->sections[$section->getId()]);
				}
			}

			# Add any new sections that aren't in the existing array
			foreach($sections as $section)
			{
				if (!array_key_exists($section->getId(),$this->sections))
				{
					$this->sections[] = $section;
					$this->newSectionIds[] = $section->getId();
				}
			}
		}
	}
?>