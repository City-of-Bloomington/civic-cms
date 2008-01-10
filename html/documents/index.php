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


	# Administrators get the full list of documents
	if (userHasRole(array('Administrator','Webmaster')))
	{
		$documentList = new DocumentList();
		$documentList->find($fields,$sort);

		$title = 'Documents';
	}
	# Non Administrators get a list of documents for only their department
	else
	{
		$fields['department_id'] = $_SESSION['USER']->getDepartment_id();
		$documentList = new DocumentList();
		$documentList->find($fields,$sort);
		$title = "{$_SESSION['USER']->getDepartment()} Documents";
	}

	# For long lists of documents, paginate the list
	if (count($documentList) > 50)
	{
		if (!isset($_GET['page'])) { $_GET['page'] = 0; }
		$pages = $documentList->getPagination(50);
		if (!$pages->offsetExists($_GET['page'])) { $_GET['page'] = 0; }
		$documents = new LimitIterator($documentList->getIterator(),$pages[$_GET['page']],$pages->getPageSize());

		$pageNavigation = new Block('pageNavigation.inc');
		$pageNavigation->page = $_GET['page'];
		$pageNavigation->pages = $pages;
		$pageNavigation->url = new URL("http://$_SERVER[SERVER_NAME]$_SERVER[REQUEST_URI]");
	}
	else { $documents = $documentList; }



	$documentsBlock = new Block('documents/documentList.inc');
	$documentsBlock->title = $title;
	$documentsBlock->documentList = $documents;


	$template = new Template('backend');
	if (isset($pageNavigation)) { $template->blocks[] = $pageNavigation; }
	$template->blocks[] = $documentsBlock;
	if (isset($pageNavigation)) { $template->blocks[] = $pageNavigation; }
	$template->render();
