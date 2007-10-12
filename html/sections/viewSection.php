<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET section_id
 *
 * Section Navigation through the site should be handled by this script.
 */
	# make sure we've got a section homepage
 	try
 	{
 		$section = new Section($_GET['section_id']);
		if ($section->getDocument_id()) { $_GET['document_id'] = $section->getDocument_id(); }
		else { throw new Exception('sections/missingHomeDocument'); }
 	}
 	catch(Exception $e) { $_SESSION['errorMessages'][] = $e; }

	$format = isset($_GET['format']) ? strtolower($_GET['format']) : 'html';
	if ($format == 'rss')
	{
		$template = new Template($format,$format);
		$block = new Block('sections/documentList.inc');
		$block->url = new URL(BASE_URL.'/sections/viewSection.php?section_id='.$section->getId());


		if (isset($_GET['featured']))
		{
			$type = new DocumentType($_GET['featured']);

			$block->documentList = new DocumentList(array('documentType_id'=>$type->getId(),'section_id'=>$section->getId(),'featured'=>1,'active'=>date('Y-m-d')));
			$block->title = Inflector::pluralize($type)." in {$section->getName()}";
		}
		else
		{
			$block->documentList = $section->getDocuments('publishDate desc');
			$block->title = $section->getName();
		}


		$template->blocks[] = $block;
		$template->render();
	}
	else { include APPLICATION_HOME.'/html/documents/viewDocument.php'; }
?>
