<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
/*
	$_GET variables:	document_id
*/
	$template = new Template();
	try
	{
		$document = new Document($_GET['document_id']);

		$template->document = $document;

		$template->widgets = $document->getWidgets();

		$template->blocks[] = new Block('breadcrumbs.inc',array('document'=>$document));
		$template->blocks[] = new Block('documents/viewDocument.inc',array('document'=>$document));
		$template->blocks[] = new Block('documents/subsections.inc',array('document'=>$document));
	}
	catch(Exception $e)
	{
		$_SESSION['errorMessages'][] = $e;
	}
	$template->render();
?>