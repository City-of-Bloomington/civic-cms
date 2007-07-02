<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET document_id
 * @param GET lang
 */
	verifyUser(array('Administrator','Webmaster'));

	$document = new Document($_GET['document_id']);
	$filename = "$_GET[document_id].$_GET[lang]";

	# Stream the File to the browser, so they can print it themselves.
	Header("Pragma: public");
	Header('Content-type: application/xhtml+xml');
	Header("Content-Disposition: attachment; filename=$filename");
	Header("Content-length: ".strlen($document->getContent($_GET['lang'])));

	echo $document->getContent($_GET['lang']);
?>