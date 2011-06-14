<?php
/**
 * @copyright Copyright (C) 2006-2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
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
										'txt'=>array('mime_type'=>'text/plain','media_type'=>'attachment'),
										'wmv'=>array('mime_type'=>'video/x-ms-wmv','media_type'=>'video'),
										'mov'=>array('mime_type'=>'video/quicktime','media_type'=>'video'),
										'rm'=>array('mime_type'=>'application/vnd.rn-realmedia','media_type'=>'video'),
										'ram'=>array('mime_type'=>'audio/vnd.rn-realaudio','media_type'=>'audio'),
										'mp3'=>array('mime_type'=>'audio/mpeg','media_type'=>'audio'),
										'mp4'=>array('mime_type'=>'video/mp4','media_type'=>'video'),
										'flv'=>array('mime_type'=>'video/x-flv','media_type'=>'video'),
										'wma'=>array('mime_type'=>'audio/x-ms-wma','media_type'=>'audio'),
										'kml'=>array('mime_type'=>'application/vnd.google-earth.kml+xml','media_type'=>'attachment'),
										'swf'=>array('mime_type'=>'application/x-shockwave-flash','media_type'=>'attachment'),
										'eps'=>array('mime_type'=>'application/postscript','media_type'=>'attachment')
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
				$PDO = Database::getConnection();

				if(is_numeric($id)) { $sql = 'select * from media where id=?'; }
				else { $sql = 'select * from media where filename=?'; }

				$query = $PDO->prepare($sql);
				$query->execute(array($id));

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
				$this->setUser($_SESSION['USER']);
				$this->department_id = $_SESSION['USER']->getDepartment_id();
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
			if (!$this->department_id) { $this->department_id = $_SESSION['USER']->getDepartment_id(); }

			$fields = array();
			$fields['filename'] = $this->filename;
			$fields['mime_type'] = $this->mime_type;
			$fields['media_type'] = $this->media_type;
			$fields['title'] = $this->title;
			$fields['description'] = $this->description ? $this->description : null;
			$fields['md5'] = $this->md5 ? $this->md5 : null;
			$fields['department_id'] = $this->department_id;
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
			$query = $PDO->prepare($sql);
			$query->execute($values);
		}

		private function insert($values,$preparedFields)
		{
			$PDO = Database::getConnection();

			$sql = "insert media set $preparedFields";
			$query = $PDO->prepare($sql);
			$query->execute($values);
			$this->id = $PDO->lastInsertID();
		}
		public function delete()
		{
			$PDO = Database::getConnection();

			# Delete the file from the hard drive
			unlink($this->getDirectory().'/'.$this->getInternalFilename());

			if ($this->id)
			{
				# Clear out the database
				$query = $PDO->prepare('delete from media_documents where media_id=?');
				$query->execute(array($this->id));

				$query = $PDO->prepare('delete from media where id=?');
				$query->execute(array($this->id));
			}
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
					throw new MediaException('media/fileAlreadyExists',$this->md5);
				}
			}


			# Clean out any previous version of the file
			if ($this->id)
			{
				foreach(glob("{$this->getDirectory()}/{$this->id}.*") as $file)
				{
					unlink($file);
				}
				# Images create a seperate cached version for each size displayed
				# We need to clear the cache, otherwise, the old version will continue showing up
				if ($this->media_type == 'image')
				{
					$image = new Image($this->id);
					$image->clearCache();
				}
			}

			# Move the file where it's supposed to go
			if (!is_dir($this->getDirectory())) { mkdir($this->getDirectory(),0777,true); }
			$newFile = $this->getDirectory().'/'.$this->getInternalFilename();
			rename($tempFile,$newFile);
			chmod($newFile,0666);

			if (!is_file($this->getDirectory().'/'.$this->getInternalFilename()))
			{
				throw new Exception('media/uploadFailed');
				exit();
			}
			else { $this->uploaded = date('Y-m-d'); }
			
			# Generate Thumbnails for Images
			if ($this->media_type == 'image')
			{
				foreach(array_keys(Image::getSizes()) as $size)
				{
					Image::resize("{$this->getDirectory()}/{$this->getInternalFilename()}",$size);
				}
			}
		}

		/**
		 * Media is stored in the data directory, outside of the web directory
		 */
		public function getDirectory()
		{
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
				$this->save();
			}
			return "{$this->id}.{$this->getExtension()}";
		}
		public function getExtension()
		{
			preg_match("/[^.]+$/",$this->filename,$matches);
			return strtolower($matches[0]);
		}


		/**
		 * @param String $size One of the sizes declared in Image::sizes
		 */
		public function getURL($size=null)
		{
			$url = BASE_URL."/media/media/{$this->mime_type}";
			$filename = $this->getInternalFilename();

			# Sizes only really apply to images
			if ($this->media_type == 'image' && $size)
			{
				$sizes = Image::getSizes();
				if (in_array($size,array_keys($sizes)))
				{
					$ext = $sizes[$size]['ext'];
					$url .= "/$size";
					$filename = "{$this->id}.$ext";
				}
			}
			$url.="/$filename";
			
			return $url;
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
		 * Alias for Upload date
		 * Media doesn't get modified, it just gets re-uploaded
		 */
		public function getModified($format)
		{
			return $this->getUploaded($format);
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

class MediaException extends Exception
{
	protected $md5;

	public function __construct($message=null,$md5=null)
	{
		parent::__construct($message);

		$this->md5 = $md5;
	}

	public function getMd5() { return $this->md5; }
}