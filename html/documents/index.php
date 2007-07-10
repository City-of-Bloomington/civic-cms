<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
	verifyUser(array('Administrator','Webmaster','Content Creator','Publisher'));

	$sort = isset($_GET['sort']) ? $_GET['sort'] : 'created desc';
	if (isset($_GET['filter']))
	{
		$filter = urldecode($_GET['filter']);
		list($field,$value) = explode('-',$filter);
		$fields = array($field=>$value);
	}
	else { $fields = null; }

	$documentsBlock = new Block('documents/documentList.inc');

	if (userHasRole(array('Administrator','Webmaster')))
	{
		$documentList = new DocumentList();
		$documentList->find($fields,$sort);

		$documentsBlock->documentList = $documentList;
		$documentsBlock->title = 'Documents';
	}
	else
	{
		$fields['department_id'] = $_SESSION['USER']->getDepartment_id();

		$list = new DocumentList($fields,$sort);
		$documentsBlock->documentList = $list;

		$documentsBlock->title = "{$_SESSION['USER']->getDepartment()} Documents";
	}

	$template = new Template('backend');
	$template->blocks[] = $documentsBlock;
	$template->render();
?>