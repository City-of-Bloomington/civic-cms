<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET document_id
 * @param array $navigation
 */
	$document = new Document($_GET['document_id']);

	$template = new Template();

	$template->document = $document;
	$template->widgets = $document->getWidgets();

	$template->blocks[] = new Block('documents/viewDocument.inc',array('document'=>$document));


	# If we don't have a specific section we're in yet,
	# choose one of the sections for this Document.
	$sections = $document->getSections();
	if (!isset($section)) { $section = $sections[0]; }


	foreach($sections as $section)
	{
		# Find out which Sections this Document is a homepage of
		if ($section->getDocument_id() === $document->getId())
		{
			# Check for Featured Documents in this Section
			$types = new DocumentTypeList();
			$types->find();
			foreach($types as $type)
			{
				$documentList = new DocumentList(array('documentType_id'=>$type->getId(),'section_id'=>$section->getId(),'featured'=>1));
				if (count($documentList))
				{
					$template->blocks[] = new Block('sections/featuredDocuments.inc',array('documentType'=>$type,'documentList'=>$documentList));
				}
			}
		}
	}

	$template->blocks[] = new Block('documents/siblings.inc',array('document'=>$document));

	$template->render();
?>