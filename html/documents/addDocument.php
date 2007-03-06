<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET documentType_id
 * @param GET section_id (Optionally include a section to pre-select)
 */
	# Make sure they're allowed to edit stuff in this section
	verifyUser(array('Administrator','Webmaster','Content Creator'));
	if (isset($_GET['section_id']))
	{
		$section = new Section($_GET['section_id']);
		if (!$section->permitsEditingBy($_SESSION['USER'])) { unset($section); }
	}

	# Create the new, empty document
	$document = new Document();
	if (isset($_GET['documentType_id']))
	{
		$document->setDocumentType_id($_GET['documentType_id']);
		$document->setTitle("New {$document->getDocumentType()}");
	}

	# If they've posted, populate the document with all their stuff
	if (isset($_POST['document']))
	{
		$document = new Document();
		$language = new Language($_POST['lang']);
		foreach($_POST['document'] as $field=>$value)
		{
			$set = "set".ucfirst($field);
			$document->$set($value);
		}
		$document->setContent($_POST['content'],$language->getCode());

		try
		{
			$document->save();
			$template = new Template('closePopup');
			$template->render();
			exit();
		}
		catch (Exception $e) { $_SESSION['errorMessages'][] = $e; }
	}


	$form = new Block('documents/addDocumentForm.inc');
	$form->document = $document;
	$form->language = isset($language) ? $language : new Language($_SESSION['LANGUAGE']);
	if (isset($section)) { $form->section = $section; }
	$form->sectionList = new SectionList(array('postable_by'=>$_SESSION['USER']));

	$template = new Template('popup');
	$template->blocks[] = $form;
	$template->render();
?>