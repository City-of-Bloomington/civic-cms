<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
/*
	$_GET variables:	document_id
*/
	verifyUser('Webmaster');

	$document = new Document($_GET['document_id']);
	$filename = basename($document->getContentFilename());

	# Stream the File to the browser, so they can print it themselves.
	Header("Pragma: public");
	Header('Content-type: application/xhtml+xml');
	Header("Content-Disposition: attachment; filename=$filename");
	Header("Content-length: ".strlen($document->getContent()));

	echo $document->getContent();
?>