<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
/*
	$_GET variables:	documentType_id
*/
	verifyUser('Webmaster');

	if (isset($_GET['documentType_id'])) { $documentType = new DocumentType($_GET['documentType_id']); }
	if (isset($_POST['documentType']))
	{
		$documentType = new DocumentType($_POST['documentType_id']);
		foreach($_POST['documentType'] as $field=>$value)
		{
			$set = "set".ucfirst($field);
			$documentType->$set($value);
		}

		try
		{
			$documentType->save();
			Header("Location: home.php");
			exit();
		}
		catch (Exception $e) { $_SESSION['errorMessages'][] = $e; }
	}

	$template = new Template();
	$template->blocks[] = new Block('documentTypes/updateDocumentTypeForm.inc',array('documentType'=>$documentType));
	$template->render();
?>