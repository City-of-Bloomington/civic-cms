<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET media_id
 *
 * Script to serve all media
 */
 	try { $media = new Media($_GET['media_id']); }
 	catch(Exception $e)
 	{
		Header('HTTP/1.0 404 Not Found');
		$_SESSION['errorMessages'][] = $e;
		$template = new Template();
		$template->render();
		exit();
 	}
	Header('Expires: 0');
	Header('Pragma: cache');
	Header('Cache-Control: private');
	Header('Content-type: '.$media->getMime_type());

	$disposition = $media->getMedia_type()=='attachment' ? 'attachment' : 'inline';
	Header("Content-Disposition: $disposition; filename=".$media->getFilename());


	readfile($media->getDirectory().'/'.$media->getInternalFilename());
?>