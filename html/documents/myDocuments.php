<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
	verifyUser();
	$sort = isset($_GET['sort']) ? $_GET['sort'] : 'created desc';

	$template = new Template('backend');

	if (userHasRole('Content Creator')) { $template->blocks[] = new Block('documents/addDocumentToolbar.inc'); }

	$userDocuments = new Block('documents/documentList.inc');
	$userDocuments->documentList = new DocumentList(array('createdBy'=>$_SESSION['USER']->getId()),$sort);
	$userDocuments->title = "{$_SESSION['USER']->getFirstname()} {$_SESSION['USER']->getLastname()}'s Documents";
	$template->blocks[] = $userDocuments;


	$departmentDocuments = new Block('documents/documentList.inc');
	$departmentDocuments->documentList = new DocumentList(array('department_id'=>$_SESSION['USER']->getDepartment_id()),$sort);
	$departmentDocuments->title = "{$_SESSION['USER']->getDepartment()} Documents";
	$template->blocks[] = $departmentDocuments;

	$template->render();
?>