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
		private $createdBy;
		private $modified;
		private $modifiedBy;
		private $department_id;

		private $department;
		private $content;
		private $contentDirectory;
		private $contentLanguage;

		private $facets = array();
		private $newFacetIds = array();
		private $deletedFacetIds = array();
		private $related = array();

		private $sections = array();
		private $deletedSections = array();
		private $newSections = array();

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
				$this->created = date("Y-m-d H:i:s");
				$this->createdBy = $_SESSION['USER']->getId();
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
			$fields['created'] = $this->created;
			$fields['modified'] = null;
			$fields['createdBy'] = $this->createdBy;
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
			$this->saveFacets();
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

			$sql = "select created from documents where id=$this->id";
			foreach($PDO->query($sql) as $row) { $this->created = $row['created']; }
		}

		private function saveContent()
		{
			$directory = $this->getContentDirectory();
			$file = "$directory/{$this->id}.$_SESSION[LANGUAGE]";

			list($year,$month,$day) = explode("-",$this->getDateCreated());

			$sandbox = new SubversionWorkingCopy(APPLICATION_HOME."/data/documents");
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
			# The database will give it an ID and a created timestamp
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


		/**
		 * Facet functions
		 */
		public function getFacets()
		{
			if (!count($this->facets))
			{
				$list = new FacetList(array('document_id'=>$this->id));
				foreach($list as $facet) { $this->facets[$facet->getId()] = $facet; }
			}
			return $this->facets;
		}
		private function saveFacets()
		{
			global $PDO;

			# Clear out all the old facets
			if (count($this->deletedFacetIds))
			{
				$ids = implode(",",$this->deletedFacetIds);
				$query = $PDO->prepare("delete from document_facets where document_id={$this->id} and facet_id in ($ids)");
				$query->execute();
			}

			# Add in the new ones
			if (count($this->newFacetIds))
			{
				$query = $PDO->prepare("insert document_facets set document_id={$this->id},facet_id=?");
				foreach($this->newFacetIds as $id) { $query->execute(array($id)); }
			}
		}
		public function setFacets(array $facetIds)
		{
			# Make sure to call $this->getFacets() at least once to ensure that
			# the current facets are loaded before trying to determine which ones are new

			# Any $facetIds that are not in $this->facets need to be added
			$this->newFacetIds = array_diff($facetIds,array_keys($this->getFacets()));
			foreach($this->newFacetIds as $id) { $this->facets[$id] = new Facet($id); }

			# Unset any $this->facets that are not in $facetIds
			$this->deletedFacetIds = array_diff(array_keys($this->facets),$facetIds);
			foreach($this->deletedFacetIds as $id) { unset($this->facets[$id]); }
		}
		public function hasFacet($facet) { return array_key_exists($facet->getId(),$this->getFacets()); }
		public function getRelatedDocuments()
		{
			global $PDO;
			if (!count($this->related))
			{
				$sql = "select distinct b.document_id,count(*) as relevance
						from document_facets d left join document_facets b using (facet_id)
						where d.document_id={$this->id} and b.document_id!={$this->id}
						group by b.document_id order by relevance";
				foreach($PDO->query($sql) as $row) { $this->related[] = new Document($row['document_id']); }
			}
			return $this->related;
		}

		/**
		 * Section functions
		 */
		public function getSections()
		{
			# A Document cannot have sections until it has an ID
			if (!count($this->sections) && $this->id)
			{
				$list = new SectionList(array('document_id'=>$this->id));
				foreach($list as $section) { $this->sections[$section->getId()] = $section; }
			}
			return $this->sections;
		}
		public function setSections(array $sectionIds)
		{
			# Make sure to call $this->getSections() at least once to ensure that
			# the current sections are loaded before trying to determine which ones are new

			# Only load the new sections the user is allowed to edit
			$newSections = array();
			foreach($sectionIds as $id)
			{
				$section = new Section($id);
				if ($section->permitsEditingBy($_SESSION['USER'])) { $newSections[$id] = $section; }
			}

			# Any Sections that are not in $this->sections need to be added
			$this->newSections = array_diff_key($newSections,$this->getSections());
			foreach($this->newSections as $id=>$section) { $this->sections[$id] = $section; }

			# Unset any $this->sections that are not in $sectionIds
			$this->deletedSections = array_diff_key($this->sections,$newSections);
			foreach($this->deletedSections as $id=>$section) { unset($this->sections[$id]); }
		}
		private function saveSections()
		{
			global $PDO;

			# Clear out any deleted sections
			if (count($this->deletedSections))
			{
				$deletedSections = implode(",",array_keys($this->deletedSections));
				$query = $PDO->prepare("delete from document_sections where document_id={$this->id} and section_id in ($deletedSections)");
				$query->execute();
			}

			# Add in any new sections
			if (count($this->newSections))
			{
				$query = $PDO->prepare("insert document_sections values($this->id,?)");
				foreach($this->newSections as $id=>$section) { $query->execute(array($id)); }
			}
		}
		public function addSection($section)
		{
			$this->newSections[$section->getId()] = $section;
			$this->sections[$section->getId()] = $section;
		}
		public function hasSection($section) { return array_key_exists($section->getId(),$this->getSections()); }


		/**
		 * Watch Functions
		 */
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


   		public function permitsEditingBy($user)
   		{
   			if ($user->hasRole(array('Webmaster','Content Creator','Administrator')) &&
   				$this->department_id = $user->getDepartment_id()) { return true; }
			return false;
   		}

		/**
		 * Generic Getters
		 */
		public function getId() { return $this->id; }
		public function getTitle() { return $this->title; }
		public function getCreated() { return $this->created; }
		public function getModified() { return $this->modified; }
		public function getCreatedBy() { return $this->createdBy; }
		public function getModifiedBy() { return $this->modifiedBy; }
		public function getDepartment_id() { return $this->department_id; }
		public function getDepartment()
		{
			if (!$this->department) { $this->department = new Department($this->department_id); }
			return $this->department;
		}
		public function getDateCreated()
		{
			list ($dateCreated,$timeCreated) = explode(' ',$this->created);
			return $dateCreated;
		}


		/**
		 * Generic Setters
		 */
		public function setTitle($string) { $this->title = trim($string); }
		public function setContent($string) { $this->content = trim($string); }
		public function setModifiedBy($user) { $this->modifiedBy = $user->getId(); }
		public function setDepartment_id($int) { $this->department = new Department($int); $this->department_id = $int; }
		public function setDepartment($department) { $this->department_id = $department->getId(); $this->department = $department; }
	}
?>