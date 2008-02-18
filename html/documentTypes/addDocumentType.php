<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
	verifyUser(array('Administrator','Webmaster'));

	if (isset($_POST['documentType']))
	{
		$documentType = new DocumentType();
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
	$template->blocks[] = new Block('documentTypes/addDocumentTypeForm.inc');
	echo $template->render();
?>