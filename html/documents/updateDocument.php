<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
/*
	$_GET variables:	document_id
*/
	verifyUser(array('Publisher','Content Creator'));

	if (isset($_GET['document_id']))
	{
		$document = new Document($_GET['document_id']);
		if (!$_SESSION['USER']->canEdit($document))
		{
			$_SESSION['errorMessages'][] = "noAccessAllowed";
			Header("Location: ".BASE_URL."/documents/viewDocument.php?document_id={$document->getId()}");
			exit();
		}
	}



	if (isset($_POST['document_id']))
	{
		$document = new Document($_POST['document_id']);

		if (!$_SESSION['USER']->canEdit($document))
		{
			$_SESSION['errorMessages'][] = "noAccessAllowed";
			Header("Location: ".BASE_URL."/documents/viewDocument.php?document_id={$document->getId()}");
			exit();
		}

		$document->setTitle($_POST['document']['title']);
		$document->setContent($_POST['content']);

		try
		{
			$document->save();
			Header("Location: ".BASE_URL."/documents/viewDocument.php?document_id={$document->getId()}");
			exit();
		}
		catch (Exception $e)
		{
			$_SESSION['errorMessages'][] = $e;
			print_r($e);
			exit();
		}
	}

	$FCKeditor = new FCKeditor("content");
	$FCKeditor->BasePath = BASE_URL."/FCKeditor/";
	$FCKeditor->ToolbarSet = 'Custom';
	if (isset($document)) { $FCKeditor->Value = $document->getContent(); }

	$template = new Template();
	$form = new Block('documents/updateDocumentForm.inc',array('document'=>$document,'FCKeditor'=>$FCKeditor));
	$template->blocks[] = $form;
	$template->render();
?>