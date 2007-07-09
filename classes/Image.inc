<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
	class Image extends Media
	{
		private $image;
		private $medium;
		private $thumbnail;

		/**
		 * The sizes, in pixels for the various versions of Images
		 */
		private $mediumSize = 300;
		private $thumbnailSize = 100;



		public function __construct($media_id=null)
		{
			parent::__construct($media_id);

			if (!$this->media_type) { $this->media_type = 'image'; }
			if ($this->media_type != 'image')
			{
				throw new Exception('media/nonimage');
			}
		}

		public function getImage()
		{
			if (!$this->image)
			{
				switch ($this->getExtension())
				{
					case 'jpg': $load = 'imagecreatefromjpeg'; break;
					case 'gif': $load = 'imagecreatefromgif'; break;
					case 'png': $load = 'imagecreatefrompng'; break;
				}
				$this->image = $load($this->getDirectory().'/'.$this->filename);
			}
			return $this->image;
		}

		/**
		 * Overrides the Media's getURL.  We want Images to be served up
		 * by PHP script, rather than creating direct URLs to them.
		 */
		public function getURL()
		{
			return BASE_URL.'/media/image.php?media_id='.$this->getId();
		}

		public function getMedium()
		{
			# Medium sized photos will always be stored as JPEG
			if (!$this->medium)
			{
				$directory = $this->getDirectory().'/medium';
				list($filename,$ext) = explode(".",$this->filename);

				# Load the medium version if it's there
				if (file_exists("$directory/$filename.jpg")) { $this->medium = imagecreatefromjpeg("$directory/$filename.jpg"); }
				else
				{
					# Otherwise, create and save a new medium version
					$this->medium = $this->resample($this->mediumSize,$this->mediumSize);
					if (!is_dir($directory)) { mkdir($directory,0777); }
					imagejpeg($this->medium,"$directory/$filename.jpg");
					chmod("$directory/$filename.jpg",0666);
				}
			}
			return $this->smallPhoto;
		}
		public function getThumbnail()
		{
			# Thumbnails will always be stored as GIF
			if (!$this->thumbnail)
			{
				$directory = $this->getDirectory().'/thumbnail';
				list($filename,$ext) = explode(".",$this->filename);

				if (file_exists("$directory/$filename.gif")) { $this->thumbnail = imagecreatefromgif("$directory/$filename.gif"); }
				else
				{
					$this->thumbnail = $this->resample($this->thumbnailSize,$this->thumbnailSize);
					if (!is_dir($directory)) { mkdir($directory,0777); }
					imagegif($this->thumbnail,"$directory/$filename.gif");
					chmod("$directory/$filename.gif",0666);
				}
			}
			return $this->thumbnail;
		}

		private function resample($width,$height)
		{
			if ($this->getWidth() < $this->getHeight()) { $width = ($height / $this->getHeight()) * $this->getWidth(); }
			else { $height = ($width / $this->getWidth()) * $this->getHeight(); }

			$scaledImage = imagecreatetruecolor($width, $height);
			imagecopyresampled($scaledImage, $this->image, 0, 0, 0, 0, $width, $height, $this->getWidth(), $this->getHeight());

			return $scaledImage;
		}

		public function getWidth() { return imagesx($this->getImage()); }
		public function getHeight() { return imagesy($this->getImage()); }
	}
?>