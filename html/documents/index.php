<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
	verifyUser(array('Administrator','Webmaster','Content Creator'));

	$sort = isset($_GET['sort']) ? $_GET['sort'] : 'created desc';

	$documentsBlock = new Block('documents/documentList.inc');

	if (userHasRole(array('Administrator','Webmaster')))
	{
		$documentList = new DocumentList();
		$documentList->find(null,$sort);

		$documentsBlock->documentList = $documentList;
		$documentsBlock->title = 'Documents';
	}
	else
	{
		$list = new DocumentList(array('department_id'=>$_SESSION['USER']->getDepartment_id()),$sort);
		$documentsBlock->documentList = $list;

		$documentsBlock->title = "{$_SESSION['USER']->getDepartment()} Documents";
	}

	$template = new Template();
	$template->blocks[] = $documentsBlock;
	$template->render();
?>