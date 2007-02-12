<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
/*
	$_GET variables:	document_id
						lang
*/
	verifyUser(array('Publisher','Content Creator'));

	if (isset($_GET['document_id']))
	{
		$document = new Document($_GET['document_id']);
		$language = isset($_GET['lang']) ? new Language($_GET['lang']) : new Language($_SESSION['LANGUAGE']);
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
		$language = new Language($_POST['lang']);

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
		$document->setContent($_POST['content'],$language->getCode());

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

	$template = new Template('popup');
	$template->blocks[] = new Block('documents/updateDocumentForm.inc',array('document'=>$document,'language'=>$language));
	$template->render();
?>