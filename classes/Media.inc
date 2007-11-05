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
		private $user_id;


		private $department;
		private $user;

		private $documents = array();

		public static $extensions = array(	'jpg'=>array('mime_type'=>'image/jpeg','media_type'=>'image'),
										'gif'=>array('mime_type'=>'image/gif','media_type'=>'image'),
										'png'=>array('mime_type'=>'image/png','media_type'=>'image'),
										'tiff'=>array('mime_type'=>'image/tiff','media_type'=>'image'),
										'pdf'=>array('mime_type'=>'application/pdf','media_type'=>'attachment'),
										'rtf'=>array('mime_type'=>'application/rtf','media_type'=>'attachment'),
										'doc'=>array('mime_type'=>'application/msword','media_type'=>'attachment'),
										'xls'=>array('mime_type'=>'application/msexcel','media_type'=>'attachment'),
										'gz'=>array('mime_type'=>'application/x-gzip','media_type'=>'attachment'),
										'zip'=>array('mime_type'=>'application/zip','media_type'=>'attachment'),
										'txt'=>array('mime_type'=>'text/plain','media_type'=>'attachment')
									);

		public static function getExtensions() { return self::$extensions; }

		/**
		 * This will load all fields in the table as properties of this class.
		 * You may want to replace this with, or add your own extra, custom loading
		 */
		public function __construct($id=null)
		{
			if ($id)
			{
				if(is_numeric($id)) { $sql = 'select * from media where id=?'; }
				elseif(strlen($id)==32) { $sql = 'select * from media where md5=?'; }
				else { $sql = 'select * from media where filename=?'; }

				$PDO = Database::getConnection();
				try
				{
					$query = $PDO->prepare($sql);
					$query->execute(array($id));
				}
				catch (Exception $e) { throw $e; }

				$result = $query->fetchAll();
				if (!count($result)) { throw new Exception('media/404'); }
				else
				{
					foreach($result[0] as $field=>$value)
					{
						if ($value) $this->$field = $value;
					}
				}
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
			$fields['department_id'] = $_SESSION['USER']->getDepartment_id();
			$fields['uploaded'] = $this->uploaded ? $this->uploaded : null;
			$fields['user_id'] = $_SESSION['USER']->getId();

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

			$sql = "update media set $preparedFields where id={$this->id}";
			if (false === $query = $PDO->prepare($sql)) { $e = $PDO->errorInfo(); throw new Exception($sql.$e[2]); }
			if (false === $query->execute($values)) { $e = $PDO->errorInfo(); throw new Exception($sql.$e[2]); }
		}

		private function insert($values,$preparedFields)
		{
			$PDO = Database::getConnection();

			$sql = "insert media set $preparedFields";
			if (false === $query = $PDO->prepare($sql)) { $e = $PDO->errorInfo(); throw new Exception($sql.$e[2]); }
			if (false === $query->execute($values)) { $e = $PDO->errorInfo(); throw new Exception($sql.$e[2]); }
			$this->id = $PDO->lastInsertID();
		}
		public function delete()
		{
			$PDO = Database::getConnection();

			# Delete the file from the hard drive
			unlink($this->getDirectory().'/'.$this->getInternalFilename());

			# Clear out the database
			$sql = "delete from media_documents where media_id={$this->id}";
			if (false === $PDO->exec($sql)) { $e = $PDO->errorInfo(); throw new Exception($sql.$e[2]); }

			$sql = "delete from media where id={$this->id}";
			if (false === $PDO->exec($sql)) { $e = $PDO->errorInfo(); throw new Exception($sql.$e[2]); }
		}

		public function setFile($file)
		{
			# Handle passing in either a $_FILES array or just a path to a file
			$tempFile = is_array($file) ? $file['tmp_name'] : $file;
			$filename = is_array($file) ? basename($file['name']) : basename($file);

			# Clean all bad characters from the filename
			$filename = $this->createValidFilename($filename);
			# Save the original filename
			$this->filename = $filename;

			if (!$tempFile) { throw new Exception('media/uploadFailed'); }

			# Find out the mime type for this file
			preg_match("/[^.]+$/",$filename,$matches);
			$extension = strtolower($matches[0]);

			if (array_key_exists(strtolower($extension),Media::$extensions))
			{
				$this->mime_type = Media::$extensions[$extension]['mime_type'];

				# We must have a media type set so before we can getDirectory()
				# To avoid overriding, uncomment the if()
				#if (!$this->media_type)
				#{
					# This is going to override any media type set by a subclass of media
					# If the user goes to upload an attachment, and it's a .jpg file
					# this will change the media_type to image, and treat it as an image,
					# not as an attachment
					$this->media_type = Media::$extensions[$extension]['media_type'];
				#}
			}
			else { throw new Exception('unknownFileType'); }

			# Make sure the file's not already in the system
			$this->md5 = md5_file($tempFile);
			$list = new MediaList(array('md5'=>$this->md5));
			if (count($list))
			{
				# If we're updating a file, we expect to get one
				# hit back - but it needs to have the current media_id
				# Otherwise, then the file is already in the system
				if ($list[0]->getId() != $this->id)
				{
					throw new Exception('media/fileAlreadyExists');
				}
			}


			# Clean out any previous version of the file
			if ($this->id)
			{
				foreach(glob($this->getDirectory().'/'.$this->id) as $file)
				{
					unlink($this->getDirectory().'/'.$file);
				}
			}

			# Move the file where it's supposed to go
			if (!is_dir($this->getDirectory())) { mkdir($this->getDirectory(),0777,true); }
			$newFile = $this->getDirectory().'/'.$this->getInternalFilename();
			rename($tempFile,$newFile);
			chmod($newFile,0666);

			if (!is_file($this->getDirectory().'/'.$this->getInternalFilename()))
			{
				echo "Upload failed\n";
				exit();
			}
			else { $this->uploaded = date('Y-m-d'); }
		}

		/**
		 * Media is stored in the data directory, outside of the web directory
		 */
		public function getDirectory()
		{
			$department = $this->createValidFilename($this->getDepartment()->getName());
			return APPLICATION_HOME."/data/media/{$this->mime_type}";
		}
		public function getInternalFilename()
		{
			# We've got a chicken-or-egg problem here.  We want to use the id
			# as the filename, but the id doesn't exist until the info's been saved
			# to the database.
			#
			# If we don't have an id yet, try and save to the database first.
			# If that fails, we most likely don't have enough required info yet
			if (!$this->id)
			{
				try { $this->save(); }
				catch(Exception $e) { throw $e; }
			}
			return "{$this->id}.{$this->getExtension()}";
		}
		public function getExtension()
		{
			preg_match("/[^.]+$/",$this->filename,$matches);
			return strtolower($matches[0]);
		}


		/**
		 *  All media will be served by scripts that stream the media to the browser
		 */
		public function getURL()
		{
			return BASE_URL."/media/media.php?media_id={$this->id}";
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

		public static function createValidFilename($string)
		{
			# No bad characters
			$string = preg_replace('/[^A-Za-z0-9_\.\s]/','',$string);

			# Convert spaces to underscores
			$string = preg_replace('/\s+/','_',$string);

			# Lower case any file extension
			if (preg_match('/(^.*\.)([^\.]+)$/',$string,$matches))
			{
				$string = $matches[1].strtolower($matches[2]);
			}

			return $string;
		}

   		public function permitsEditingBy($user)
   		{
   			if ($user->hasRole(array('Webmaster','Administrator','Publisher'))) { return true; }
   			if ($user->hasRole('Content Creator') && $this->department_id == $user->getDepartment_id()) { return true; }
			return false;
   		}

		public function getFilesize()
		{
			return filesize($this->getDirectory().'/'.$this->getInternalFilename());
		}

		/**
		 * Generic Getters
		 */
		public function getId() { return $this->id; }
		public function getFilename() { return $this->filename; }
		public function getMime_type() { return $this->mime_type; }
		public function getMedia_type() { return $this->media_type; }
		public function getType() { return $this->media_type; }
		public function getTitle() { return $this->title; }
		public function getDescription() { return $this->description; }
		public function getMd5() { return $this->md5; }
		public function getDepartment_id() { return $this->department_id; }
		public function getUploaded($format=null)
		{
			if ($format && $this->uploaded!=0) return strftime($format,strtotime($this->uploaded));
			else return $this->uploaded;
		}
		public function getUser_id() { return $this->user_id; }
		public function getUser()
		{
			if (!$this->user) { $this->user = new User($this->user_id); }
			return $this->user;
		}

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
		public function setUploadedBy($int) { $this->user = new User($int); $this->user_id = $this->user->getId(); }
		public function setUser($user) { $this->user_id = $user->getId(); $this->user = $user; }

		public function setDepartment($department) { $this->department_id = $department->getId(); $this->department = $department; }
	}
?>
