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
		private $wikiTitle;
		private $alias;
		private $feature_title;
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
		private $related = array();

		private $sections = array();

		private $widgets = array();
		private $attachments = array();

		/**
		 * This will load all fields in the table as properties of this class.
		 * You may want to replace this with, or add your own extra, custom loading
		 */
		public function __construct($id=null)
		{
			if ($id)
			{
				if (is_numeric($id)) { $sql = "select * from documents where id=?"; }
				else { $sql = "select * from documents where title=?"; }

				$PDO = Database::getConnection();
				$query = $PDO->prepare($sql);
				$query->execute(array($id));

				$result = $query->fetchAll();
				if (!count($result)) { throw new Exception('documents/unknownDocument'); }
				foreach($result[0] as $field=>$value) { if ($value) $this->$field = $value; }
			}
			else
			{
				# This is where the code goes to generate a new, empty instance.
				# Set any default values for properties that need it here
				$this->created = date('Y-m-d H:i:s');
				$this->createdBy = $_SESSION['USER']->getId();
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
			if (!$this->wikiTitle) { $this->wikiTitle = WikiMarkup::wikify($this->title); }

			# Make sure we've got something for content
			$hasContent = false;
			foreach($this->getContent() as $lang=>$content)
			{
				if ($content)
				{
					$hasContent = true;
					break;
				}
			}
			if (!$hasContent) { throw new Exception('documents/missingContent'); }

			$fields = array();
			$fields['title'] = $this->title;
			$fields['wikiTitle'] = $this->wikiTitle;
			$fields['alias'] = $this->alias ? $this->alias : null;
			$fields['feature_title'] = $this->feature_title ? $this->feature_title : null;
			$fields['created'] = $this->created ? $this->created : date('Y-m-d H:i:s');
			$fields['modified'] = null;
			$fields['createdBy'] = $this->createdBy;
			$fields['modifiedBy'] = $_SESSION['USER']->getId();
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

			$this->saveContent();
			$this->saveFacets();
		}

		private function update($values,$preparedFields)
		{
			$PDO = Database::getConnection();

			$sql = "update documents set $preparedFields where id={$this->id}";
			$query = $PDO->prepare($sql);
			$query->execute($values);
		}

		private function insert($values,$preparedFields)
		{
			$PDO = Database::getConnection();

			$sql = "insert documents set $preparedFields";
			$query = $PDO->prepare($sql);
			$query->execute($values);
			$this->id = $PDO->lastInsertID();
		}

		public function delete()
		{
			if ($this->id)
			{
				$PDO = Database::getConnection();

				# Documents that are the home page for a section should not be deleted
				$sections = new SectionList(array('document_id'=>$this->id));
				if (count($sections))
				{
					throw new Exception('documents/sectionHomepage');
				}

				$this->deleteContent();

				$query = $PDO->prepare("delete from documentLinks where document_id={$this->id}");
				$query->execute();

				$query = $PDO->prepare("delete from document_watches where document_id={$this->id}");
				$query->execute();

				$query = $PDO->prepare("update sections set document_id=null where document_id={$this->id}");
				$query->execute();

				$query = $PDO->prepare("delete from sectionDocuments where document_id={$this->id}");
				$query->execute();

				$query = $PDO->prepare("delete from document_facets where document_id={$this->id}");
				$query->execute();

				$query = $PDO->prepare("delete from media_documents where document_id={$this->id}");
				$query->execute();

				$query = $PDO->prepare("delete from documents where id={$this->id}");
				$query->execute();

				foreach($this->getWatches() as $watch) { $watch->notify("Document: '{$this->getTitle()}' has been deleted\n"); }
			}
		}

		/**
		 * @param string $string content markup
		 * @param string $lang Two-letter language code
		 */
		public function setContent($string,$lang)
		{
			if (!$this->isLocked())
			{
				if (defined('HTMLPURIFIER'))
				{
					require_once HTMLPURIFIER.'/HTMLPurifier.auto.php';
					include APPLICATION_HOME.'/HTMLPurifier_Config.inc';

					$purifier = new HTMLPurifier($config);
					$string = $purifier->purify($string);
				}
				$this->content[$lang] = trim($string);
			}
		}
		/**
		 * @param string $string content source code
		 * @param string $lang Two-letter language code
		 * Seperate function to handle raw source code that doesn't get
		 * cleaned or purified
		 */
		public function setSource($string,$lang)
		{
			if (!$this->isLocked()) { $this->content[$lang] = trim($string); }
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
				if ($lang)
				{
					if (!isset($this->content[$lang])) { $this->content[$lang] = ''; }
					return $this->content[$lang];
				}
				else { return $this->content; }
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
			if ($this->id)
			{
				if (!count($this->facets))
				{
					$list = new FacetList(array('document_id'=>$this->id));
					foreach($list as $facet) { $this->facets[$facet->getId()] = $facet; }
				}
			}
			return $this->facets;
		}
		private function saveFacets()
		{
			$PDO = Database::getConnection();
			$facets = $this->getFacets();

			$sql = "delete from document_facets where document_id={$this->id}";
			if (false === $PDO->exec($sql)) { $e = $PDO->errorInfo(); throw new Exception($sql.$e[2]); }

			$query = $PDO->prepare('insert document_facets values(?,?)');
			foreach($facets as $facet_id=>$facet)
			{
				$query->execute(array($this->id,$facet_id));
			}
		}
		public function setFacets(array $facet_ids)
		{
			$this->facets = array();
			foreach($facet_ids as $facet_id) { $this->facets[$facet_id] = new Facet($facet_id); }
		}
		public function hasFacet($facet) { return array_key_exists($facet->getId(),$this->getFacets()); }
		public function getRelatedDocuments()
		{
			if (!count($this->related))
			{
				$PDO = Database::getConnection();
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
		public function getSectionDocuments()
		{
			if ($this->id)
			{
				return new SectionDocumentList(array('document_id'=>$this->id));
			}
			return array();
		}
		public function getSections()
		{
			if (!count($this->sections))
			{
				foreach($this->getSectionDocuments() as $sectionDocument)
				{
					$this->sections[$sectionDocument->getSection_id()] = $sectionDocument->getSection();
				}
			}
			return $this->sections;
		}
		public function addSection($section)
		{
			$section_id = ($section instanceof Section) ? $section->getId() : $section;
			$list = new SectionDocumentList(array('document_id'=>$this->id,'section_id'=>$section_id));
			if (!count($list))
			{
				$sectionDocument = new SectionDocument();
				$sectionDocument->setDocument_id($this->id);
				$sectionDocument->setSection_id($section_id);
				$sectionDocument->save();
			}
		}
		public function removeSection($sectionDocument_id)
		{
			$sectionDocument = new SectionDocument($sectionDocument_id);
			$sectionDocument->delete();
		}
		public function hasSection($section)
		{
			if(in_array($section->getId(),array_keys($this->getSections()))) { return true; }
			return false;
		}

		public function isFeaturedIn($section)
		{
			foreach($this->getSectionDocuments() as $sectionDocument)
			{
				if ($sectionDocument->getSection_id()==$section->getId())
				{
					return $sectionDocument->getFeatured();
				}
			}
		}

		public function isHomepage()
		{
			foreach($this->getSections() as $section)
			{
				if ($section->getDocument_id() == $this->id) { return true; }
			}
			return false;
		}


		/**
		 * Watch Functions
		 */
		public function addWatch($user)
		{
			$PDO = Database::getConnection();

			$query = $PDO->prepare("insert document_watches values(?,?)");
			$query->execute(array($this->id,$user->getId()));
		}
		public function removeWatch($user)
		{
			$PDO = Database::getConnection();

			$query = $PDO->prepare("delete from document_watches where document_id=? and user_id=?");
			$query->execute(array($this->id,$user->getId()));
		}
		public function getWatches()
		{
			$PDO = Database::getConnection();

			$watches = array();
			foreach($PDO->query("select * from document_watches where document_id={$this->id}") as $row)
			{
				$watches[] = new Watch($this->id,$row['user_id']);
			}
			return $watches;
		}


   		public function permitsEditingBy($user)
   		{
   			if ($user->hasRole(array('Webmaster','Administrator','Publisher'))) { return true; }
   			if ($user->hasRole('Content Creator') && $this->department_id == $user->getDepartment_id()) { return true; }
			return false;
   		}

		public function getWidgets($search=null)
   		{
			# If a document doesn't have any Sections, we've got bigger problems.
			# But we know that you can't find any widgets, so don't try to look them up
			if (count($this->getSections()))
			{
				$sectionIds = array_keys($this->getSections());

				if (is_array($search)) { $search['section_id_array'] = $sectionIds; }
				else { $search = array('section_id_array'=>$sectionIds); }
				$this->widgets = new SectionWidgetList($search);
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
					$list = new MediaList(array('document_id'=>$this->id));
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
   			if (!in_array($media->getId(),array_keys($this->getAttachments())))
   			{
				$PDO = Database::getConnection();
				$query = $PDO->prepare('insert media_documents values(?,?)');
				$query->execute(array($media->getId(),$this->id));

				$this->attachments[$media->getId()] = $media;
   			}
   		}
   		public function addAttachment($media) { $this->attach($media); }
   		public function removeAttachment($media)
   		{
			if (is_int($media)) { $media = new Media($media); }

			if (in_array($media->getId(),array_keys($this->getAttachments())))
			{
				$PDO = Database::getConnection();
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
		public function getAlias() { return $this->alias; }
		public function getFeature_title() { return $this->feature_title; }
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
		 * Return a URL that can always navigate to this document
		 */
		public function getURL()
		{
			return BASE_URL.'/documents/viewDocument.php?document_id='.$this->id;
		}

		/**
		 * Generic Setters
		 */
		public function setTitle($string)
		{
			$this->title = trim($string);
			$this->wikiTitle = WikiMarkup::wikify($this->title);
		}
		public function setAlias($string) { $this->alias = WikiMarkup::wikify($string); }
		public function setFeature_title($string) { $this->feature_title = trim($string); }
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
