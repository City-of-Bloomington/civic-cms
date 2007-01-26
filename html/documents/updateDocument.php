<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
/*
	$_GET variables:	document_id
						return_url
						( lang ) Optional - handled in configuration.inc
*/
	verifyUser(array('Publisher','Content Creator'));

	if (isset($_GET['document_id']))
	{
		$document = new Document($_GET['document_id']);
		if (!$document->permitsEditingBy($_SESSION['USER']))
		{
			$_SESSION['errorMessages'][] = "noAccessAllowed";
			$template = new Template('closePopup');
			$template->render();
			exit();
		}
	}



	if (isset($_POST['document']))
	{
		$document = new Document($_POST['document_id']);

		if (!$document->permitsEditingBy($_SESSION['USER']))
		{
			$_SESSION['errorMessages'][] = "noAccessAllowed";
			Header("Location: ".BASE_URL."/documents/viewDocument.php?document_id={$document->getId()}");
			exit();
		}
		foreach($_POST['document'] as $field=>$value)
		{
			$set = "set".ucfirst($field);
			$document->$set($value);
		}
		$document->setContent($_POST['content']);

		try
		{
			$document->save();
			$template = new Template('closePopup');
			$template->render();
			exit();
		}
		catch (Exception $e)
		{
			$_SESSION['errorMessages'][] = $e;
			print_r($_POST);
			exit();
		}
	}

	$FCKeditor = new FCKeditor("content");
	$FCKeditor->BasePath = BASE_URL."/FCKeditor/";
	$FCKeditor->ToolbarSet = 'Custom';
	if (isset($document)) { $FCKeditor->Value = $document->getContent(); }

	$form = new Block('documents/updateDocumentForm.inc');
	$form->FCKeditor = $FCKeditor;
	$form->document = $document;

	$template = new Template('popup');
	$template->blocks[] = $form;
	$template->render();
?>