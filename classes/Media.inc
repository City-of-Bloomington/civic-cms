<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
	class Media extends ActiveRecord
	{

		private $id;
		protected $filename;
		protected $mime_type;
		protected $media_type;
		private $title;
		private $description;
		protected $md5;
		private $department_id;
		private $uploaded;
		private $uploadedBy;


		private $department;

		private $documents = array();
		private $newDocumentIds = array();
		private $deletedDocumentIds = array();

		protected $mime_types = array(	'jpg'=>'image/jpeg',
										'gif'=>'image/gif',
										'png'=>'image/png',
										'tiff'=>'image/tiff',
										'pdf'=>'application/pdf',
										'rtf'=>'application/rtf',
										'doc'=>'application/msword',
										'xls'=>'application/msexcel',
										'gz'=>'application/x-gzip',
										'zip'=>'application/zip',
										'txt'=>'text/plain'
									);
		/**
		 * This will load all fields in the table as properties of this class.
		 * You may want to replace this with, or add your own extra, custom loading
		 */
		public function __construct($id=null)
		{
			global $PDO;

			if ($id)
			{
				$sql = 'select * from media where id=?';
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
				$this->department_id = $_SESSION['USER']->getDepartment_id();
				$this->uploadedBy = $_SESSION['USER']->getId();
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
			if (!$this->filename || !$this->mime_type || !$this->media_type) { throw new Exception('missingRequiredFields'); }
			if (!$this->title) { throw new Exception('media/missingTitle'); }
			if (!$this->description) { throw new Exception('media/missingDescription'); }

			$fields = array();
			$fields['filename'] = $this->filename;
			$fields['mime_type'] = $this->mime_type;
			$fields['media_type'] = $this->media_type;
			$fields['title'] = $this->title;
			$fields['description'] = $this->description ? $this->description : null;
			$fields['md5'] = $this->md5 ? $this->md5 : null;
			$fields['department_id'] = $this->department_id ? $this->department_id : null;
			$fields['uploaded'] = $this->uploaded ? $this->uploaded : null;
			$fields['uploadedBy'] = $this->uploadedBy ? $this->uploadedBy : null;

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

			$this->saveDocuments();
		}

		private function update($values,$preparedFields)
		{
			global $PDO;

			$sql = "update media set $preparedFields where id={$this->id}";
			if (false === $query = $PDO->prepare($sql)) { $e = $PDO->errorInfo(); throw new Exception($sql.$e[2]); }
			if (false === $query->execute($values)) { $e = $PDO->errorInfo(); throw new Exception($sql.$e[2]); }
		}

		private function insert($values,$preparedFields)
		{
			global $PDO;

			$sql = "insert media set $preparedFields";
			if (false === $query = $PDO->prepare($sql)) { $e = $PDO->errorInfo(); throw new Exception($sql.$e[2]); }
			if (false === $query->execute($values)) { $e = $PDO->errorInfo(); throw new Exception($sql.$e[2]); }
			$this->id = $PDO->lastInsertID();
		}

		public function setFile($file)
		{
			if (!is_dir($this->getDirectory())) { mkdir($this->getDirectory(),0770,true); }

			# Handle passing in either a $_FILES array or just a path to a file
			if (is_array($file)) { $newFile = $this->getDirectory().'/'.basename($file['name']); }
			else { $newFile = $this->getDirectory.'/'.basename($file); }


			# Find out the mime type for this file
			preg_match("/[^.]+$/",$newFile,$matches);
			$extension = $matches[0];
			if (array_key_exists($extension,$this->mime_types))
			{
				$this->mime_type = $this->mime_types[$extension];
			}
			else { throw new Exception('unknownFileType'); }


			# Make sure the file's not already in the system
			$this->md5 = md5_file($newFile);
			$list = new MediaList(array('md5'=>$this->md5));
			if (count($list)) { throw new Exception('media/fileAlreadyExists'); }

			# Move the file where it's supposed to go
			if (is_array($file)) { move_uploaded_file($file['tmp_name'],$newFile); }
			else { rename($file,$newFile); }

			# Save the filename
			$this->filename = basename($newFile);
		}

		public function getDirectory()
		{
			return APPLICATION_HOME."/html/media/{$this->media_type}/{$this->getDepartment()->getName()}";
		}
		public function getURL()
		{
			$department = $this->getDepartment()->getName();
			$file = $this->filename;
			return BASE_URL."/media/{$this->media_type}/$department/$file";
		}
		public function getExtension()
		{
			preg_match("/[^.]+$/",$this->filename,$matches);
			return $matches[0];
		}

		/**
		 * Document functions
		 */
		public function getDocuments()
		{
			# The media has to have been saved before it can have documents
			# associated with it in the database
			if ($this->id)
			{
				if (!count($this->documents))
				{
					$list = new DocumentList(array('media_id'=>$this->id));
					echo $list->getSQL();
					foreach($list as $document) { $this->documents[$document->getId()] = $document; }
				}
			}
			return $this->documents;
		}
		private function saveDocuments()
		{
			global $PDO;

			# Clear out all the old facets
			if (count($this->deletedDocumentIds))
			{
				$ids = implode(",",$this->deletedDocumentIds);
				$query = $PDO->prepare("delete from media_documents where media_id={$this->id} and document_id in ($ids)");
				$query->execute();
			}

			# Add in the new ones
			if (count($this->newDocumentIds))
			{
				$query = $PDO->prepare("insert media_documents set media_id={$this->id},document_id=?");
				foreach($this->newDocumentIds as $id) { $query->execute(array($id)); }
			}
		}
		public function addDocument($document)
		{
			if (!array_key_exists($document->getId(),$this->getDocuments()))
			{
				$this->documents[$document->getId()] = $document;
				$this->newDocumentIds[] = $document->getId();
			}
		}
		public function setDocuments(array $documentIds)
		{
			# Make sure to call $this->getDocuments() at least once to ensure that
			# the current documents are loaded before trying to determine which ones are new

			# Any $documentIds that are not in $this->documents need to be added
			$this->newDocumentIds = array_diff($documentIds,array_keys($this->getDocuments()));
			foreach($this->newDocumentIds as $id) { $this->Documents[$id] = new Document($id); }

			# Unset any $this->documents that are not in $documentIds
			$this->deletedDocumentIds = array_diff(array_keys($this->documents),$documentIds);
			foreach($this->deletedDocumentIds as $id) { unset($this->documents[$id]); }
		}
		public function hasDocument($document) { return array_key_exists($document->getId(),$this->getFacets()); }


		/**
		 * Generic Getters
		 */
		public function getId() { return $this->id; }
		public function getFilename() { return $this->filename; }
		public function getType() { return $this->type; }
		public function getTitle() { return $this->title; }
		public function getDescription() { return $this->description; }
		public function getMd5() { return $this->md5; }
		public function getDepartment_id() { return $this->department_id; }
		public function getUploaded($format=null)
		{
			if ($format && $this->uploaded!=0) return strftime($format,strtotime($this->uploaded));
			else return $this->uploaded;
		}
		public function getUploadedBy() { return $this->uploadedBy; }

		public function getDepartment()
		{
			if ($this->department_id)
			{
				if (!$this->department) { $this->department = new Department($this->department_id); }
				return $this->department;
			}
			else return null;
		}

		/**
		 * Generic Setters
		 */
		public function setTitle($string) { $this->title = trim($string); }
		public function setDescription($string) { $this->description = trim($string); }
		public function setDepartment_id($int) { $this->department = new Department($int); $this->department_id = $int; }
		public function setUploaded($timestamp) { $this->uploaded = is_array($timestamp) ? $this->dateArrayToString($timestamp) : $timestamp; }
		public function setUploadedBy($int) { $this->uploadedBy = ereg_replace("[^0-9]","",$int); }

		public function setDepartment($department) { $this->department_id = $department->getId(); $this->department = $department; }

	}
?>