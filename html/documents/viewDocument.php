<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
/*
	$_GET variables:	document_id
*/
	$template = new Template();
	$document = new Document($_GET['document_id']);
	$template->document = $document;

	$template->blocks[] = new Block("breadcrumbs.inc",array('document'=>$document));

	if (userHasRole("Content Creator") && $_SESSION['USER']->getDepartment_id()==$document->getDepartment_id())
	{
		$template->blocks[] = new Block("documents/toolbar.inc",array('document'=>$document));
	}

	$template->blocks[] = new Block("documents/viewDocument.inc",array('document'=>$document));
	$template->render();
?>