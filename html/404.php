<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
	$title = urldecode(basename($_SERVER['REQUEST_URI']));
	$title = str_replace('_',' ',$title);

	$list = new DocumentList(array('title'=>$title));
	switch (count($list))
	{
		case 0:
			echo "
			<h2>404 Not Found</h2>
			<p>$title</p>
			";
		break;

		case 1:
			$document = $list[0];
			$_GET['document_id'] = $document->getId();
			include APPLICATION_HOME.'/html/documents/viewDocument.php';
		break;

		default:
			$template = new Template();
			$template->blocks[] = new Block('documents/searchResults.inc',array('results'=>$list));
			$template->render();
	}
?>