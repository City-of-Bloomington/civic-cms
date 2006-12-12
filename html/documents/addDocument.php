<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
/*
	$_GET variables:	return_url
						section_id  ( Optionally include a section to pre-select )
*/
	verifyUser(array('Publisher','Content Creator'));

	if (isset($_GET['section_id']))
	{
		$section = new Section($_GET['section_id']);
		if (!$section->permitsEditingBy($_SESSION['USER'])) { unset($section); }
	}

	if (isset($_POST['document']))
	{
		$document = new Document();
		foreach($_POST['document'] as $field=>$value)
		{
			$set = "set".ucfirst($field);
			$document->$set($value);
		}
		$document->setContent($_POST['content']);

		try
		{
			$document->save();
			#Header("Location: ".BASE_URL."/documents/viewDocument.php?document_id={$document->getId()}");
			exit();
		}
		catch (Exception $e) { $_SESSION['errorMessages'][] = $e; }
	}

	$FCKeditor = new FCKeditor("content");
	$FCKeditor->BasePath = BASE_URL."/FCKeditor/";
	$FCKeditor->ToolbarSet = 'Custom';
	if (isset($document)) { $FCKeditor->Value = $document->getContent(); }

	$form = new Block('documents/addDocumentForm.inc');
	$form->FCKeditor = $FCKeditor;
	$form->response = new URL($_GET['return_url']);
	if (isset($section)) { $form->section = $section; }

	$template = new Template();
	$template->blocks[] = $form;
	$template->render();
?>