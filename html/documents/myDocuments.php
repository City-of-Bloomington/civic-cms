<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
	verifyUser();

	$template = new Template();

	$userDocumentList = new DocumentList(array('createdBy'=>$_SESSION['USER']->getId()),'created desc');
	$template->blocks[] = new Block('documents/userDocuments.inc',array('documentList'=>$userDocumentList,'user'=>$_SESSION['USER']));

	$departmentDocumentList = new DocumentList(array('department_id'=>$_SESSION['USER']->getDepartment_id()),'created desc');
	$template->blocks[] = new Block('documents/departmentDocuments.inc',array('documentList'=>$departmentDocumentList,'department'=>$_SESSION['USER']->getDepartment()));

	$template->render();
?>