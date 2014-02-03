<?php
/**
 * @copyright 2006-2014 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
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
	if (count($documentList) > 50) 	{
		$page = !empty($_GET['page']) ? (int)$_GET['page'] : 1;

		$documents = $documentList->getPagination(50);
		$documents->setCurrentPageNumber($page);

		$pageNavigation = new Block('pageNavigation.inc', ['paginator'=>$documents]);
	}
	else { $documents = $documentList; }



	$documentsBlock = new Block('documents/documentList.inc');
	$documentsBlock->title = $title;
	$documentsBlock->documentList = $documents;


	$template = new Template('backend');
	if (isset($pageNavigation)) { $template->blocks[] = $pageNavigation; }
	$template->blocks[] = $documentsBlock;
	if (isset($pageNavigation)) { $template->blocks[] = $pageNavigation; }
	echo $template->render();
