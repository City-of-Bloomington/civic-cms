<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET document_id
 * @param POST document_id
 * @param array $navigation
 *
 * Documents in the system that have forms should post to themselves.
 * Forms must include document_id as a hidden field.
 * Documents that include forms are expected to have the PHP code
 * inside themselves to process their own POST
 */
	$template = new Template();

	if (isset($_GET['document_id'])) { $document = new Document($_GET['document_id']); }
	if (isset($_POST['document_id'])) { $document = new Document($_POST['document_id']); }

	if (isset($document))
	{
		$template->document = $document;

		$template->blocks[] = new Block('documents/viewDocument.inc',array('document'=>$document));


		# If we don't have a specific section we're in yet,
		# choose one of the sections for this Document.
		$sections = $document->getSections();
		if (!isset($section))
		{
			# The section list returned will not be zero based.  To get the
			# first element, you have to call current()
			$section = count($sections) ? current($sections) : null;
		}


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
					$documentList = new DocumentList(array('documentType_id'=>$type->getId(),'section_id'=>$section->getId(),'featured'=>1,'active'=>date('Y-m-d')));
					if (count($documentList))
					{
						$template->blocks[] = new Block('sections/featuredDocuments.inc',array('documentType'=>$type,'documentList'=>$documentList));
					}
				}
			}
		}

		$template->blocks[] = new Block('documents/siblings.inc',array('document'=>$document));
	}
	else { $_SESSION['errorMessages'][] = new Exception('documents/unknownDocument'); }

	$template->render();
?>