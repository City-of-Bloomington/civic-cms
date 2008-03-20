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

				exec(IMAGEMAGICK."/convert $originalFile -resize '{$dimension}x{$dimension}>' -background white -flatten $newFile");
			}

			readfile("$directory/$filename.$ext");
		}
		else
		{
			throw new Exception('media/unknownSize');
		}
	}

	/**
	 * Delete any cached preview version of this image
	 */
	public function clearCache()
	{
		foreach($this->sizes as $size=>$info)
		{
			foreach(glob("{$this->getDirectory()}/$size/{$this->getId()}.*") as $file)
			{
				unlink($file);
			}
		}
	}


	/**
	 * Returns the width of the requested version of an image
	 * @param string $size The version of the image (see $this->sizes)
	 */
	public function getWidth($size=null)
	{
		if ($size)
		{
			return exec(IMAGEMAGICK."/identify -format '%w' {$this->getDirectory()}/$size/{$this->getId()}.{$this->sizes[$size]['ext']}");
		}
		else
		{
			# Return the size of the original
			return exec(IMAGEMAGICK."/identify -format '%w' {$this->getDirectory()}/{$this->getInternalFilename()}");
		}
	}

	/**
	 * Returns the height of the requested version of an image
	 * @param string $size The version of the image (see $this->sizes)
	 */
	public function getHeight($size=null)
	{
		if ($size)
		{
			return exec(IMAGEMAGICK."/identify -format '%h' {$this->getDirectory()}/$size/{$this->getId()}.{$this->sizes[$size]['ext']}");
		}
		else
		{
			# Return the size of the original
			return exec(IMAGEMAGICK."/identify -format '%h' {$this->getDirectory()}/{$this->getInternalFilename()}");
		}
	}
}
