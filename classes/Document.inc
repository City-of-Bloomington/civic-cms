<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
	class Document extends ActiveRecord
	{
		private $id;
		private $title;
		private $created;
		private $createdBy;
		private $modified;
		private $modifiedBy;
		private $publishDate;
		private $retireDate;
		private $department_id;
		private $documentType_id;
		private $description;
		private $lockedBy;
		private $enablePHP;

		private $department;
		private $content = array();
		private $contentDirectory;
		private $documentType;
		private $lockedByUser;

		private $facets = array();
		private $newFacetIds = array();
		private $deletedFacetIds = array();
		private $related = array();

		private $sections = array();
		private $document_sections = array();

		private $widgets = array();
		private $attachments = array();

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
				if (!count($result)) { throw new Exception('documents/unknownDocument'); }
				foreach($result[0] as $field=>$value) { if ($value) $this->$field = $value; }
			}
			else
			{
				# This is where the code goes to generate a new, empty instance.
				# Set any default values for properties that need it here
				$this->created = date("Y-m-d H:i:s");
				$this->createdBy = $_SESSION['USER']->getId();
				$this->modifiedBy = $_SESSION['USER']->getId();
				$this->publishDate = $this->created;
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
			if (!$this->department_id) { throw new Exception('missingRequiredFields'); }
			if (!$this->title) { throw new Exception('documents/missingTitle'); }
			if (!count($this->getDocumentSections())) { throw new Exception('documents/missingSection'); }#if (!$this->description) { throw new Exception('missingDescription'); }

			$fields = array();
			$fields['title'] = $this->title;
			$fields['created'] = $this->created;
			$fields['modified'] = null;
			$fields['createdBy'] = $this->createdBy;
			$fields['modifiedBy'] = $this->modifiedBy;
			$fields['publishDate'] = $this->publishDate ? $this->publishDate : null;
			$fields['retireDate'] = $this->retireDate ? $this->retireDate : null;
			$fields['department_id'] = $this->department_id;
			$fields['documentType_id'] = $this->documentType_id ? $this->documentType_id : null;
			$fields['description'] = $this->description ? $this->description : null;
			$fields['lockedBy'] = $this->lockedBy ? $this->lockedBy : null;
			$fields['enablePHP'] = $this->enablePHP ? 1 : 0;

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

			$search = new Search();
			$search->updateDocument($this);
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

			$search = new Search();
			$search->addDocument($this);
		}

		public function delete()
		{
			global $PDO;
			foreach($this->getWatches() as $watch) { $watch->notify("Document: '{$this->getTitle()}' has been deleted\n"); }

			$search = new Search();
			$search->removeDocument($this);

			$this->deleteContent();

			$query = $PDO->prepare("delete from document_watches where document_id={$this->id}");
			$query->execute();

			$query = $PDO->prepare("update sections set document_id=null where document_id={$this->id}");
			$query->execute();

			$query = $PDO->prepare("delete from document_sections where document_id={$this->id}");
			$query->execute();

			$query = $PDO->prepare("delete from document_facets where document_id={$this->id}");
			$query->execute();

			$query = $PDO->prepare("delete from media_documents where document_id={$this->id}");
			$query->execute();

			$query = $PDO->prepare("delete from documents where id={$this->id}");
			$query->execute();
		}

		/**
		 * Content Related Functions
		 */
		public function setContent($string,$lang)
		{
			if (!$this->isLocked())
			{
				$this->content[$lang] = trim($string);
			}
		}
		private function saveContent()
		{
			$directory = $this->getContentDirectory();
			foreach($this->content as $lang=>$content)
			{
				$file = "$directory/{$this->id}.$lang";

				list($year,$month,$day) = explode("-",substr($this->created,0,10));

				$sandbox = new SubversionWorkingCopy(APPLICATION_HOME.'/data/documents');
				if (!is_dir($directory))
				{
					mkdir($directory,0775,true);
					$sandbox->add(APPLICATION_HOME."/data/documents/$year","--force");
				}
				file_put_contents($file,$this->content[$lang]);

				$out = $sandbox->status($file);
				if (count($out) && $out[0]{0} == "?") { $sandbox->add($file); }
			}
			$sandbox->commit(APPLICATION_HOME."/data/documents/$year",$_SESSION['USER']->getUsername());


			# Inform the people on the watch list
			foreach($this->getWatches() as $watch) { $watch->notify(); }
		}
		private function deleteContent()
		{
			if (!$this->isLocked())
			{
				$sandbox = new SubversionWorkingCopy(APPLICATION_HOME.'/data/documents');
				$directory = $this->getContentDirectory();
				foreach(glob("$directory/{$this->id}.*") as $file)
				{
					$sandbox->delete($file);
				}
				$sandbox->commit($directory,$_SESSION['USER']->getUsername());
			}
		}
		public function getContent($lang=null)
		{
			# Content won't exist as a file until it's been saved to the database
			# The database will give it an ID and a created timestamp
			if ($this->id)
			{
				# If they ask for a certain language
				$directory = $this->getContentDirectory();
				if ($lang)
				{
					# Return only the requested language content
					if (!isset($this->content[$lang]))
					{
						if (file_exists("$directory/{$this->id}.$lang"))
						{
							$this->content[$lang] = file_get_contents("$directory/{$this->id}.$lang");
						}
						else { $this->content[$lang] = ''; }
					}
					return $this->content[$lang];
				}
				else
				{
					# Otherwise, return the entire array of language content
					foreach(glob("$directory/{$this->id}.*") as $content)
					{
						list($id,$ext) = explode('.',basename($content));
						if (!isset($this->content[$ext])) { $this->content[$ext] = file_get_contents($content); }
					}
					return $this->content;
				}
			}
			# Before content is saved, there still might be a template loaded into
			# the content array for a given lang
			else
			{
				if ($lang && isset($this->content[$lang])) { return $this->content[$lang]; }
				else { return null; }
			}
		}
		private function getContentDirectory()
		{
			if (!$this->contentDirectory)
			{
				list($year,$month,$day) = explode("-",substr($this->created,0,10));
				$this->contentDirectory = APPLICATION_HOME."/data/documents/$year/$month/$day";
			}
			return $this->contentDirectory;
		}
		public function getContentFilename($lang=null)
		{
			if (!$lang) { $lang = $_SESSION['LANGUAGE']; }
			$filename = "{$this->getContentDirectory()}/{$this->id}.$lang";
			if (file_exists($filename)) { return $filename; }
			else return null;
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
				foreach($PDO->query($sql) as $row) { $this->related[$row['document_id']] = new Document($row['document_id']); }
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
		public function getDocumentSections()
		{
			global $PDO;

			if ($this->id)
			{
				if (!count($this->document_sections))
				{
					$query = $PDO->prepare('select * from document_sections where document_id=?');
					$query->execute(array($this->id));
					$result = $query->fetchAll();
					foreach($result as $row)
					{
						$this->document_sections[$row['section_id']] = array('id'=>$row['section_id'],'featured'=>$row['featured']);
					}
				}
			}
			return $this->document_sections;

		}
		/**
		 * Set the array of sections linked to this document
		 * $sections must be an array in the form of:
		 * $sections[$section_id]['id'] = $section_id;
		 * $sections[$section_id]['featured'] = 0|1 <<optional>>
		 */
		public function setSections(array $sections)
		{
			$this->document_sections = $sections;
		}
		private function saveSections()
		{
			global $PDO;

			if ($this->id)
			{
				$query = $PDO->prepare('delete from document_sections where document_id=?');
				$query->execute(array($this->id));

				$query = $PDO->prepare('insert document_sections values(?,?,?)');
				foreach($this->document_sections as $section_id=>$section)
				{
					$featured = isset($section['featured']) ? $section['featured'] : 0;
					$query->execute(array($this->id,$section_id,$featured));
				}
			}
		}
		public function addSection($section,$featured=0)
		{
			$this->document_sections[$section->getId()] = array('id'=>$section->getId(),'featured'=>$featured);
			$this->sections[$section->getId()] = $section;
		}
		public function hasSection($section) { return array_key_exists($section->getId(),$this->getSections()); }

		public function isFeaturedIn($section)
		{
			if (array_key_exists($section->getId(),$this->getDocumentSections()))
			{
				if (isset($this->document_sections[$section->getId()]['featured']))
				{
					return $this->document_sections[$section->getId()]['featured'];
				}
				return 0;
			}
			return 0;
		}


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
   			if (	($user->hasRole(array('Webmaster','Administrator','Publisher'))) ||
   					($user->hasRole('Content Creator') && $this->department_id = $user->getDepartment_id())
   				)
   			{ return true; }
			return false;
   		}

		public function getWidgets($search=null)
   		{
   			global $PDO;

			if (!count($this->widgets))
			{
				# If a document doesn't have any Sections, we've got bigger problems.
				# But we know that you can't find any widgets, so don't try to look them up
				if (count($this->getSections()))
				{
					$sectionIds = array_keys($this->getSections());
					foreach($this->getSections() as $section)
					{
						foreach($section->getAncestors() as $vector)
						{
							foreach($vector as $ancestor) { if (!in_array($ancestor->getId(),$sectionIds)) { $sectionIds[] = $ancestor->getId(); } }
						}
					}


					if (is_array($search)) { $search['section_id_array'] = $sectionIds; }
					else { $search = array('section_id_array'=>$sectionIds); }
					$this->widgets = new SectionWidgetList($search);
				}
			}
			return $this->widgets;
   		}

   		/**
   		 * Attachment functions
   		 * Attachments need to be linked immediately.  Do not wait until the document is saved
   		 * Attachments do require a document_id, though
   		 */
   		public function getAttachments()
   		{
			if ($this->id)
			{
				if (!count($this->attachments))
				{
					$list = new AttachmentList(array('document_id'=>$this->id));
					foreach($list as $attachment)
					{
						$this->attachments[$attachment->getId()] = $attachment;
					}
				}
			}
			return $this->attachments;
   		}
   		public function attach($media)
   		{
   			global $PDO;

   			if (!in_array($media->getId(),array_keys($this->getAttachments())))
   			{
				$query = $PDO->prepare('insert media_documents values(?,?)');
				$query->execute(array($media->getId(),$this->id));

				$this->attachments[$media->getId()] = $media;
   			}
   		}
   		public function addAttachment($media) { $this->attach($media); }
   		public function removeAttachment($media)
   		{
   			global $PDO;

			if (is_int($media)) { $media = new Media($media); }

			if (in_array($media->getId(),array_keys($this->getAttachments())))
			{
				$query = $PDO->prepare('delete from media_documents where media_id=? and document_id=?');
				$query->execute(array($media->getId(),$this->id));

				unset($this->attachments[$media->getId()]);
			}
   		}

   		public function isLocked() { return $this->lockedBy ? true : false; }
   		public function PHPIsEnabled() { return $this->enablePHP ? true : false; }


		/**
		 * Generic Getters
		 */
		public function getId() { return $this->id; }
		public function getTitle() { return $this->title; }
		public function getCreated($format=null)
		{
			if ($format && $this->created!=0) return strftime($format,strtotime($this->created));
			else return $this->created;
		}
		public function getModified($format=null)
		{
			if ($format && $this->modified!=0) return strftime($format,strtotime($this->modified));
			else return $this->modified;
		}
		public function getPublishDate($format=null)
		{
			if ($format && $this->publishDate!=0) return strftime($format,strtotime($this->publishDate));
			else return $this->publishDate;
		}
		public function getRetireDate($format=null)
		{
			if ($format && $this->retireDate!=0) return strftime($format,strtotime($this->retireDate));
			else return $this->retireDate;
		}
		public function getCreatedBy() { return $this->createdBy; }
		public function getModifiedBy() { return $this->modifiedBy; }
		public function getDepartment_id() { return $this->department_id; }
		public function getDocumentType_id() { return $this->documentType_id; }
		public function getDescription() { return $this->description; }
		public function getModifiedByUser() { return new User($this->modifiedBy); }
		public function getLockedBy() { return $this->lockedBy; }
		public function getEnablePHP() { return $this->enablePHP; }
		public function getLockedByUser()
		{
			if (!$this->lockedByUser)
			{
				if ($this->lockedBy) { $this->lockedByUser = new User($this->lockedBy); }
			}
			return $this->lockedByUser;
		}
		public function getDepartment()
		{
			if (!$this->department) { $this->department = new Department($this->department_id); }
			return $this->department;
		}
		public function getDocumentType()
		{
			if ($this->documentType_id)
			{
				if (!$this->documentType) { $this->documentType = new DocumentType($this->documentType_id); }
				return $this->documentType;
			}
			else return null;
		}

		/**
		 * Generic Setters
		 */
		public function setTitle($string) { $this->title = trim($string); }
		public function setModifiedBy($user) { $this->modifiedBy = $user->getId(); }
		public function setPublishDate($date) { $this->publishDate = is_array($date) ? $this->dateArrayToString($date) : $date; }
		public function setRetireDate($date) { $this->retireDate = is_array($date) ? $this->dateArrayToString($date) : $date; }
		public function setDepartment_id($int) { $this->department = new Department($int); $this->department_id = $int; }
		public function setDepartment($department) { $this->department_id = $department->getId(); $this->department = $department; }
		public function setDescription($string) { $this->description = trim($string); }
		public function setEnablePHP($int) { $this->enablePHP = $int ? 1 : 0; }
		public function setLockedBy($int=null)
		{
			if ($int)
			{
				$this->lockedByUser = new User($int);
				$this->lockedBy = $int;
			}
			else
			{
				$this->lockedByUser = null;
				$this->lockedBy = null;
			}
		}
		public function setLockedByUser($user) { $this->lockedBy = $user->getId(); $this->lockedByUser = $user; }
		public function setDocumentType_id($int,$lang=null)
		{
			$this->documentType = new DocumentType($int);
			$this->documentType_id = $int;
			# Only load the default template if $lang is passed
			if ($lang)
			{
				if (!isset($this->content[$lang])) { $this->content[$lang] = $this->documentType->getTemplate(); }
			}
		}
		public function setDocumentType($type,$lang=null)
		{
			$this->documentType_id = $type->getId();
			$this->documentType = $type;
			# Only load the default template if $lang is passed
			if ($lang)
			{
				if (!isset($this->content[$lang])) { $this->content[$lang] = $this->documentType->getTemplate(); }
			}
		}
	}
?>