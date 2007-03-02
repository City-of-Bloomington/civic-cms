<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
	verifyUser(array('Administrator','Webmaster','Content Creator'));

	$sort = isset($_GET['sort']) ? $_GET['sort'] : 'created desc';

	$documentsBlock = new Block('documents/documentList.inc');

	if (userHasRole(array('Administrator','Webmaster')))
	{
		$documentList = new DocumentList();
		$documentList->find();

		$documentsBlock->documentList = $documentList;
		$documentsBlock->title = 'Documents';
	}
	else
	{
		$documentsBlock->documentList = new DocumentList(array('department_id'=>$_SESSION['USER']->getDepartment_id()),$sort);
		$documentsBlock->title = "{$_SESSION['USER']->getDepartment()} Documents";
	}

	$template = new Template('backend');
	$template->blocks[] = new Block('documents/addDocumentToolbar.inc');
	$template->blocks[] = $documentsBlock;
	$template->render();
?>