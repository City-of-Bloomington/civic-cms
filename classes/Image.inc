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
	private static $sizes = array(	'medium'=>array('size'=>350,'ext'=>'jpg'),
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
	 * Uses self::$sizes to predefine known sizes and extensions
	 * @param string $size Must be an entry in self::$sizes
	 */
	public function output($size='medium')
	{
		if ($size == 'original') { readfile($this->getDirectory().'/'.$this->getInternalFilename()); }
		elseif (in_array($size,array_keys(self::$sizes)))
		{
			$directory = $this->getDirectory()."/$size";
			if ($this->getId()) { $filename = $this->getId(); }
			else
			{
				preg_match('/(^.*)\.([^\.]+)$/',$this->filename,$matches);
				$filename = $matches[1];
			}

			$ext = self::$sizes[$size]['ext'];
			if (!is_file("$directory/$filename.$ext"))
			{
				self::resize("{$this->getDirectory()}/{$this->getInternalFilename()}",$size);
			}

			readfile("$directory/$filename.$ext");
		}
		else
		{
			throw new Exception('media/unknownSize');
		}
	}
	
	/**
	 * Uses ImageMagick to create a thumbnail file for the given image
	 * Input must be a full path.
	 * The resized image file will be saved in $inputPath/$size/$inputFilename.$ext
	 * The sizes array determines the output filetype (gif,jpg,png)
	 * ie. /var/www/sites/photobase/uploads/username/something.jpg
	 * @param string $inputFile Full path to an image file
	 * @param string $size The name of the size desired.  Names are defined in the Media class
	 */
	public static function resize($inputFile,$size)
	{
		if (in_array($size,array_keys(self::$sizes)))
		{
			$directory = dirname($inputFile)."/$size";

			preg_match('/(^.*)\.([^\.]+)$/',basename($inputFile),$matches);
			$filename = $matches[1];

			$ext = self::$sizes[$size]['ext'];

			if (!is_dir($directory)) { mkdir($directory,0777,true); }

			$dimension = self::$sizes[$size]['size'];
			$newFile = "$directory/$filename.$ext";
			exec(IMAGEMAGICK."/convert $inputFile -resize '{$dimension}x{$dimension}>' $newFile");
		}
		else { throw new Exception('media/unknownSize'); }
	}

	/**
	 * Delete any cached preview version of this image
	 */
	public function clearCache()
	{
		foreach(self::$sizes as $size=>$info)
		{
			foreach(glob("{$this->getDirectory()}/$size/{$this->getId()}.*") as $file)
			{
				unlink($file);
			}
		}
	}


	/**
	 * Returns the width of the requested version of an image
	 * @param string $size The version of the image (see self::$sizes)
	 */
	public function getWidth($size=null)
	{
		if ($size)
		{
			$file = "{$this->getDirectory()}/$size/{$this->getId()}.".self::$sizes[$size]['ext'];
		}
		else
		{
			# Return the size of the original
			$file = "{$this->getDirectory()}/{$this->getInternalFilename()}";
		}
		return exec(IMAGEMAGICK."/identify -format '%w' $file");
	}

	/**
	 * Returns the height of the requested version of an image
	 * @param string $size The version of the image (see self::$sizes)
	 */
	public function getHeight($size=null)
	{
		if ($size)
		{
			$file = "{$this->getDirectory()}/$size/{$this->getId()}.".self::$sizes[$size]['ext'];
		}
		else
		{
			# Return the size of the original
			$file = "{$this->getDirectory()}/{$this->getInternalFilename()}";
		}
		return exec(IMAGEMAGICK."/identify -format '%h' $file");
	}
	
	public static function getSizes() { return self::$sizes; }
}
