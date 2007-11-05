<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET media_id
 *
 * Script to serve all media
 */
 	if ($_GET['media_id'])
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
		catch(Exception $e) { }
	}

	if (!isset($media))
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
	readfile("$path/$internalFilename");
