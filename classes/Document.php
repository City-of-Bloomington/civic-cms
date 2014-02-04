<?php
/**
 * @copyright 2006-2009 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
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
		private $banner_media_id;
		private $icon_media_id;
		private $skin;

		private $department;
		private $content = array();
		private $contentDirectory;
		private $documentType;
		private $lockedByUser;

		private $related = array();

		private $sections = array();

		private $widgets = array();
		private $attachments = array();
		private $banner;
		private $icon;

		/**
		 * This will load all fields in the table as properties of this class.
		 * You may want to replace this with, or add your own extra, custom loading
		 */
		public function __construct($id=null)
		{
			if ($id)
			{
				if (is_numeric($id)) { $sql = 'select * from documents where id=?'; }
				else { $sql = 'select * from documents where title=?'; }

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
		 * Throws an exception if there's anything wrong
		 *  @throws Exception
		 */
		public function validate()
		{
			if (!$this->department_id) {
				throw new Exception('missingRequiredFields');
			}
			if (!$this->title) {
				throw new Exception('documents/missingTitle');
			}
			if (!$this->wikiTitle) {
				$this->wikiTitle = WikiMarkup::wikify($this->title);
			}

			// Make sure the title is unique
			$pdo = Database::getConnection();
			$query = $pdo->prepare('select id from documents where title=?');
			$query->execute(array($this->title));
			$result = $query->fetchAll(PDO::FETCH_ASSOC);
			foreach ($result as $row) {
				if ($row['id'] != $this->id) {
					throw new Exception('documents/duplicateTitle');
				}
			}
		}


		/**
		 * This generates generic SQL that should work right away.
		 * You can replace this $fields code with your own custom SQL
		 * for each property of this class,
		 */
		public function save()
		{
			$this->validate();

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
			$fields['banner_media_id'] = $this->banner_media_id ? $this->banner_media_id : null;
			$fields['icon_media_id'] = $this->icon_media_id ? $this->icon_media_id : null;
			$fields['skin'] = $this->skin ? $this->skin : null;

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
				if ($this->isHomepage())
				{
					throw new Exception('documents/sectionHomepage');
				}

				$query = $PDO->prepare('delete from documentLinks where document_id=?');
				$query->execute(array($this->id));

				$query = $PDO->prepare('delete from document_watches where document_id=?');
				$query->execute(array($this->id));

				$query = $PDO->prepare('delete from sectionDocuments where document_id=?');
				$query->execute(array($this->id));

				$query = $PDO->prepare('delete from document_facets where document_id=?');
				$query->execute(array($this->id));

				$query = $PDO->prepare('delete from media_documents where document_id=?');
				$query->execute(array($this->id));

				$this->deleteContent();

				$query = $PDO->prepare('delete from documents where id=?');
				$query->execute(array($this->id));

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
				if (defined('TIDY_CONFIG'))
				{
					$string = tidy_repair_string($string,TIDY_CONFIG);
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
			if (!$this->isLocked()) {
				$this->content[$lang] = trim($string);
				$search = new Search();
				$search->add($this);
				$search->commit();
			}
		}
		private function saveContent()
		{
			$directory = $this->getContentDirectory();
			foreach($this->content as $lang=>$content)
			{
				# Make sure content isn't empty
				if ($content)
				{
					$file = "$directory/{$this->id}.$lang";

					list($year,$month,$day) = explode("-",substr($this->created,0,10));

					if (!is_dir($directory))
					{
						mkdir($directory,0775,true);
					}
					file_put_contents($file,$this->content[$lang]);

					if ($this->PHPIsEnabled())
					{
						$output = shell_exec(PHP." -l $file");
						if (!preg_match('/^No syntax errors detected/',$output))
						{
							throw new PHPSyntaxException('documents/PHPSyntaxError',$output);
						}
					}
				}
				else
				{
					# Delete the empty language content
					$this->deleteContent($lang);
				}
			}

			# Inform the people on the watch list
			foreach($this->getWatches() as $watch) { $watch->notify(); }

			# Update the search index
			$search = new Search();
			$search->add($this);
			$search->commit();
		}
		private function deleteContent($lang='*')
		{
			if (!$this->isLocked())
			{
				$directory = $this->getContentDirectory();
				foreach(glob("$directory/{$this->id}.$lang") as $file)
				{
					unlink($file);
				}

				# Update the Search index
				$search = new Search();
				$search->delete($this);
				$search->commit();
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
		 * @return FacetGroupList
		 */
		public function getFacetGroups()
		{
			return new FacetGroupList(array('document_id'=>$this->id));
		}

		/**
		 * Returns facets for the document.
		 *
		 * You can pass in additional search parameters
		 *
		 * @param FacetGroup $facetGroup
		 * @return FacetList
		 */
		public function getFacets(array $fields=null)
		{
			if ($this->id) {
				$search = array('document_id'=>$this->id);
				if ($fields) {
					$search = array_merge($search,$fields);
				}
				return new FacetList($search);
			}
			return array();
		}
		/**
		 * Takes an array of id numbers for facets and saves them to the database
		 * @param array $facet_ids The array of ID numbers for the facets
		 */
		public function setFacets(array $facet_ids)
		{
			$PDO = Database::getConnection();

			$query = $PDO->prepare('delete from document_facets where document_id=?');
			$query->execute(array($this->id));

			$query = $PDO->prepare('insert document_facets values(?,?)');
			foreach($facet_ids as $facet_id)
			{
				$query->execute(array($this->id,$facet_id));
			}
		}
		/**
		 * @param Facet $facet
		 * @return boolean
		 */
		public function hasFacet($facet)
		{
			$PDO = Database::getConnection();
			$query = $PDO->prepare('select facet_id from document_facets where document_id=? and facet_id=?');
			$query->execute(array($this->id,$facet->getId()));
			$result = $query->fetchAll();
			return count($result) ? true : false;
		}
		public function getRelatedDocuments()
		{
			if (!count($this->related))
			{
				$PDO = Database::getConnection();
				$sql = "select distinct b.document_id,count(*) as relevance
						from document_facets d left join document_facets b using (facet_id)
						where d.document_id=? and b.document_id!=?
						group by b.document_id order by relevance";
				$query = $PDO->prepare($sql);
				$query->execute(array($this->id,$this->id));
				$result = $query->fetchAll();
				foreach($result as $row) { $this->related[$row['document_id']] = new Document($row['document_id']); }
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

		/**
		 * Tells whether this document is a homepage.
		 *
		 * If you pass it a Section, it will tell you whether this document
		 * is the homepage for that section.  Otherwise, it will tell you
		 * if the document is a homepage for any of it's sections
		 * @param Section $section
		 */
		public function isHomepage(Section $section=null)
		{
			if ($section)
			{
				return $section->getDocument_id() == $this->id;
			}
			else
			{
				foreach($this->getSections() as $section)
				{
					if ($section->getDocument_id() == $this->id) { return true; }
				}
				return false;
			}
		}

		/**
		 * Gives you a list of Sections this document is the homepage of
		 */
		public function getHomeSections()
		{
			return new SectionList(array('homeDocument_id'=>$this->id));
		}

		/**
		 * Watch Functions
		 */
		public function addWatch($user)
		{
			$PDO = Database::getConnection();

			$query = $PDO->prepare('insert document_watches values(?,?)');
			$query->execute(array($this->id,$user->getId()));
		}
		public function removeWatch($user)
		{
			$PDO = Database::getConnection();

			$query = $PDO->prepare('delete from document_watches where document_id=? and user_id=?');
			$query->execute(array($this->id,$user->getId()));
		}
		public function getWatches()
		{
			$PDO = Database::getConnection();

			$query = $PDO->prepare('select * from document_watches where document_id=?');
			$query->execute(array($this->id));
			$result = $query->fetchAll();

			$watches = array();
			foreach($result as $row)
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
		public function isActive()
		{
			$now = time();
			$publish = strtotime($this->publishDate);
			$retire = $this->retireDate ? strtotime($this->retireDate) : null;

			return ($publish < $now && (!$retire || $now < $retire));
		}

		public function logAccess()
		{
			if ($this->id)
			{
				DocumentAccessLog::logHit($this);
			}
		}

		public function getDocumentLinks()
		{
			return new DocumentLinkList(array('document_id'=>$this->id));
		}

		/**
		 * Creates an array of sections representing the best path this Document,
		 * to be used as breadcrumbs
		 * @param int $currentSectionId The section where the user currently is
		 * @param int $previousSectionId The section where the user just was
		 */
		public function getBreadcrumbs($currentSectionId=null,$previousSectionId=null)
		{
			#------------------------------------------------------------
			# Set up the breadcrumbs
			#------------------------------------------------------------
			$ancestors = array();
			foreach($this->getSections() as $parent)
			{
				$temp = $parent->getAncestors();
				foreach($temp as $i=>$vector) { $temp[$i][$parent->getId()] = $parent; }

				$ancestors = array_merge($ancestors,$temp);
			}

			if ($currentSectionId)
			{
				# The vector needs to start with our current section
				foreach($ancestors as $vector)
				{
					$ids = array_reverse(array_keys($vector));
					if ($ids[0] == $currentSectionId)
					{
						# Choose a vector that has the previous section as the second element
						if (!$previousSectionId || (isset($ids[1]) && $ids[1]==$previousSectionId))
						{
							# This vector looks as good as any
							$currentAncestors = $vector;
							break;
						}
					}
				}
			}
			elseif($previousSectionId)
			{
				# Try and find a vector that has the previous section first
				foreach($ancestors as $vector)
				{
					$ids = array_reverse(array_keys($vector));
					if ($ids[0] == $previousSectionId)
					{
						$currentAncestors = $vector;
						break;
					}
				}
				# If we still haven't found a vector to use
				if (!isset($currentAncestors))
				{
					# Try and find a vector that has the previous section second
					foreach($ancestors as $vector)
					{
						$ids = array_reverse(array_keys($vector));
						if (isset($ids[1]) && $ids[1] == $previousSectionId)
						{
							$currentAncestors = $vector;
							break;
						}
					}
				}
			}

			if (!isset($currentAncestors))
			{
				# Just choose the shortest vector
				$shortest_length = 0;

				foreach($ancestors as $vector)
				{
					$ids = array_reverse(array_keys($vector));

					$numAncestors = count($ids);
					if (!$shortest_length || $numAncestors<$shortest_length)
					{
						$shortest_length = $numAncestors;
						$currentAncestors = $vector;
					}
				}
			}

			return isset($currentAncestors) ? $currentAncestors : array();
		}

		/**
		 * Return a URL that can always navigate to this document
		 * @return URL
		 */
		public function getURL()
		{
			if ($this->getAlias()) {
				return new URL(BASE_URL.'/'.$this->getAlias());
			}
			else {
				return new URL(BASE_URL.'/documents/viewDocument.php?document_id='.$this->id);
			}
		}

		/**
		 * Returns an array of fields that are publically displayable about this class
		 * $array[shortname] = 'Display Name'
		 * @return array
		 */
		public static function getDisplayableFields()
		{
			return array('id'=>'ID',
						'title'=>'Title',
						'wikiTitle'=>'Wiki Title',
						'alias'=>'Alias',
						'feature_title'=>'Feature Title',
						'created'=>'Created Date',
						'createdBy'=>'Created By Username',
						'createdByFullname'=>'Created By Fullname',
						'modified'=>'Modified Date',
						'modifiedBy'=>'Modified By Username',
						'publishDate'=>'Publish Date',
						'retireDate'=>'Retire Date',
						'department'=>'Department'
						);
		}

		/**
		 * Returns all the displayable fields that were chosen in this
		 * Document's DocumentType
		 * @return array
		 */
		public function getInfo()
		{
			$info = array();
			foreach($this->getDocumentType()->getDocumentInfoFields() as $field)
			{
				switch ($field)
				{
					case 'createdBy':
						$info[$field] = $this->getCreatedByUser()->getUsername();
						break;
					case 'createdByFullname':
						$info[$field] = "{$this->getCreatedByUser()->getFirstname()} {$this->getCreatedByUser()->getLastname()}";
						break;

					case 'modifiedBy':
						$info[$field] = $this->getModifiedByUser()->getUsername();
						break;

					default:
						$getter = 'get'.ucfirst($field);
						$info[$field] = $this->$getter();
				}

				if (!$info[$field])
				{
					$fields = $this->getDisplayableFields();
					$info[$field] = "Please add a(n) $fields[$field] to this {$this->getDocumentType()->getType()}";
				}
			}
			return $info;
		}

		public function getBanner() { return $this->getBanner_media(); }
		public function setBanner() { return $this->setBanner_media(); }

		/**
		 * Generic Getters
		 */
		public function getId() { return $this->id; }
		public function getTitle() { return $this->title; }
		public function getWikiTitle() { return $this->wikiTitle; }
		public function getAlias() { return $this->alias; }
		public function getFeature_title() { return $this->feature_title; }
		public function getCreated($format=null)
		{
			if ($format && $this->created)
			{
				if (strpos($format,'%')!==false) { return strftime($format,strtotime($this->created)); }
				else { return date($format,strtotime($this->created)); }
			}
			else return $this->created;
		}
		public function getModified($format=null)
		{
			if ($format && $this->modified)
			{
				if (strpos($format,'%')!==false) { return strftime($format,strtotime($this->modified)); }
				else { return date($format,strtotime($this->modified)); }
			}
			else return $this->modified;
		}
		public function getPublishDate($format=null)
		{
			if ($format && $this->publishDate)
			{
				if (strpos($format,'%')!==false) { return strftime($format,strtotime($this->publishDate)); }
				else { return date($format,strtotime($this->publishDate)); }
			}
			else return $this->publishDate;
		}
		public function getRetireDate($format=null)
		{
			if ($format && $this->retireDate)
			{
				if (strpos($format,'%')!==false) { return strftime($format,strtotime($this->retireDate)); }
				else { return date($format,strtotime($this->retireDate)); }
			}
			else return $this->retireDate;
		}
		/**
		 * @return int The user_id of the person who created this Document
		 */
		public function getCreatedBy() { return $this->createdBy; }

		/**
		 * @return User The User object of the person who created this Document
		 */
		public function getCreatedByUser() { return new User($this->createdBy); }
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
		public function getBanner_media_id() { return $this->banner_media_id; }
		public function getBanner_media()
		{
			if ($this->banner_media_id && !$this->banner)
			{
				$this->banner = new Media($this->banner_media_id);
			}
			return $this->banner;
		}
		public function getIcon_media_id() { return $this->icon_media_id; }
		public function getIcon_media()
		{
			if ($this->icon_media_id)
			{
				if (!$this->icon) { $this->icon = new Media($this->icon_media_id); }
				return $this->icon;
			}
		}
		public function getSkin() { return $this->skin; }


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
		public function setBanner_media_id($int) { $this->banner = new Media($int); $this->banner_media_id = $int; }
		public function setBanner_media($media) { $this->banner_media_id = $media->getId(); $this->banner = $media; }
		public function setIcon_media_id($int) { $this->icon = new Media($int); $this->icon_media_id = $this->icon->getId(); }
		public function setIcon_media($media) { $this->icon_media_id = $media->getId(); $this->icon = $media; }
		public function setSkin($CSSDirectoryName) { $this->skin = trim($CSSDirectoryName); }
	}

class PHPSyntaxException extends Exception
{
	private $detail;

	public function __construct($message,$detail)
	{
		parent::__construct($message,0);
		$this->detail = $detail;
	}

	public function getDetail() { return $this->detail; }
}
