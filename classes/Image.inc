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
	private $sizes = array('medium'=>array('size'=>350,'ext'=>'jpg'),
						   'thumbnail'=>array('size'=>100,'ext'=>'gif')
						   );


	public function __construct($media_id=null)
	{
		parent::__construct($media_id);

		if (!$this->media_type) { $this->media_type = 'image'; }
		if ($this->media_type != 'image')
		{
			throw new Exception('media/nonimage');
		}
	}

	/**
	 * Generates, caches, and outputs preview versions of images
	 * Uses $this->sizes to predefine known sizes and extensions
	 * @param string $size Must be an entry in $this->sizes
	 */
	public function output($size='medium')
	{
		if ($size == 'original') { readfile($this->getDirectory().'/'.$this->getInternalFilename()); }
		elseif (in_array($size,array_keys($this->sizes)))
		{
			$directory = $this->getDirectory()."/$size";
			if ($this->getId()) { $filename = $this->getId(); }
			else
			{
				preg_match('/(^.*)\.([^\.]+)$/',$this->filename,$matches);
				$filename = $matches[1];
			}

			$ext = $this->sizes[$size]['ext'];
			if (!is_file("$directory/$filename.$ext"))
			{
				if (!is_dir($directory)) { mkdir($directory,0777,true); }

				$originalFile = "{$this->getDirectory()}/$filename.{$this->getExtension()}";
				$newFile = "$directory/$filename.$ext";

				$dimension = $this->sizes[$size]['size'];

				exec(IMAGEMAGICK."/convert $originalFile -resize '{$dimension}x{$dimension}>' $newFile");
			}

			readfile("$directory/$filename.$ext");
		}
		else
		{
			throw new Exception('media/unknownSize');
		}
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
