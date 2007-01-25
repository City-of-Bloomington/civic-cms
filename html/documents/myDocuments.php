<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
	verifyUser();

	$template = new Template();

	$userDocuments = new Block('documents/documentList.inc');
	$userDocuments->documentList = new DocumentList(array('createdBy'=>$_SESSION['USER']->getId()),'created desc');
	$userDocuments->title = "{$_SESSION['USER']->getFirstname()} {$_SESSION['USER']->getLastname()}'s Documents";
	$template->blocks[] = $userDocuments;


	$departmentDocuments = new Block('documents/documentList.inc');
	$departmentDocuments->documentList = new DocumentList(array('department_id'=>$_SESSION['USER']->getDepartment_id()),'created desc');
	$departmentDocuments->title = "{$_SESSION['USER']->getDepartment()} Documents";
	$template->blocks[] = $departmentDocuments;

	$template->render();
?>