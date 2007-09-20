<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
	$section = new Section(1);
	$document = new Document(1);
	$template = new Template('blank');


	$template->document = $document;
	$template->title = $document->getTitle();

	$template->blocks[] = new Block('documents/viewDocument.inc',array('document'=>$document));


	# Check for Featured Documents in this Section
	$types = new DocumentTypeList();
	$types->find();
	foreach($types as $type)
	{
		$documentList = new DocumentList(array('documentType_id'=>$type->getId(),'section_id'=>$section->getId(),'featured'=>1,'active'=>date('Y-m-d')));
		if (count($documentList))
		{
			$featuredDocuments = new Block('sections/featuredDocuments.inc');
			$featuredDocuments->documentType = $type;
			$featuredDocuments->documentList = $documentList;
			$featuredDocuments->section = $section;

			$template->blocks[] = $featuredDocuments;
		}
	}

	$template->blocks[] = new Block('documents/siblings.inc',array('document'=>$document));

	$template->render();
?>