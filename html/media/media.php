<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET media_id
 * @param GET size (optional for Images)
 *
 * Script to serve all media
 */
if (isset($_GET['media_id']) && $_GET['media_id'])
{
	try
	{
		$media = new Media($_GET['media_id']);

		$mime = $media->getMime_type();
		$disposition = $media->getMedia_type()=='attachment' ? 'attachment' : 'inline';
		$filename = $media->getFilename();
		$path = $media->getDirectory();
		$internalFilename = $media->getInternalFilename();
	}
	catch(Exception $e)
	{
		$mime = 'image/png';
		$disposition = 'inline';
		$filename = 'missing.png';
		$path = APPLICATION_HOME.'/html/media';
		$internalFilename = $filename;
	}
}
else
{
	$mime = 'image/png';
	$disposition = 'inline';
	$filename = 'missing.png';
	$path = APPLICATION_HOME.'/html/media';
	$internalFilename = $filename;
}

Header('Expires: 0');
Header('Pragma: cache');
Header('Cache-Control: private');
Header("Content-type: $mime");
Header("Content-Disposition: $disposition; filename=$filename");

if (isset($media) && $media->getMedia_type() == 'image')
{
	$size = (isset($_GET['size'])&&$_GET['size']) ? $_GET['size'] : 'medium';
	$image = new Image($media->getId());
	$image->output($size);
}
else { readfile("$path/$internalFilename"); }
