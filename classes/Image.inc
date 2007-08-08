<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
	class Image extends Media
	{
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

		public function outputImage()
		{
			readfile($this->getDirectory().'/'.$this->getInternalFilename());
		}

		public function outputMedium()
		{
			$directory = $this->getDirectory().'/medium';
			$filename = $this->getId();

			# Medium sized photos will always be stored as JPEG
			if (!is_file("$directory/$filename.jpg"))
			{
				if (!is_dir($directory)) { mkdir($directory,0777,true); }

				$originalFile = $this->getDirectory().'/'.$this->getInternalFilename();
				$newFile = "$directory/$filename.jpg";

				exec(IMAGEMAGICK."/convert $originalFile -resize '{$this->mediumSize}x{$this->mediumSize}>' $newFile");
			}

			readfile("$directory/$filename.gif");
		}

		public function outputThumbnail()
		{
			$directory = $this->getDirectory().'/thumbnail';
			$filename = $this->getId();

			# Thumbnails will always be stored as GIF
			if (!is_file("$directory/$filename.gif"))
			{
				if (!is_dir($directory)) { mkdir($directory,0777,true); }

				$originalFile = $this->getDirectory().'/'.$this->getInternalFilename();
				$newFile = "$directory/$filename.gif";

				exec(IMAGEMAGICK."/convert $originalFile -resize '{$this->thumbnailSize}x{$this->thumbnailSize}>' $newFile");
			}

			readfile("$directory/$filename.gif");
		}


		public function getWidth()
		{
			return exec(IMAGEMAGICK."/identify -format '%w' {$this->getDirectory()}/{$this->getInternalFilename()}");
		}
		public function getHeight()
		{
			return exec(IMAGEMAGICK."/identify -format '%h' {$this->getDirectory()}/{$this->getInternalFilename()}");
		}
	}
?>