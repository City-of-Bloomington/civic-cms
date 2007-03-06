<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param POST document_id
 * @param POST lang
 * @param POST content
 */
	verifyUser(array('Administrator','Webmaster'));

	$document = new Document($_POST['document_id']);
	$document->setContent(file_get_contents($_FILES['content']['tmp_name']),$_POST['lang']);

	try
	{
		$document->save();
		$template = new Template('closePopup');
		$template->render();
		exit();
	}
	catch (Exception $e) { $_SESSION['errorMessages'][] = $e; }

	Header("Location: updateDocument.php?document_id={$document->getId()};lang=$_POST[lang]");
?>