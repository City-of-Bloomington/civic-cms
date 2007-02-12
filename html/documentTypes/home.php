<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
	verifyUser('Webmaster');

	$list = new DocumentTypeList();
	$list->find();

	$template = new Template('backend');
	$template->blocks[] = new Block('documentTypes/documentTypeList.inc',array('documentTypeList'=>$list));
	$template->render();
?>