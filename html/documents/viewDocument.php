<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
/*
	$_GET variables:	document_id
*/
	$template = new Template();
	$template->blocks[] = new Block("documents/viewDocument.inc",array('document'=>new Document($_GET['document_id'])));
	$template->render();
?>