<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
/*
	$_POST variables:	document_id
						content
*/
	verifyUser('Webmaster');

	$document = new Document($_POST['document_id']);
	$document->setContent(file_get_contents($_FILES['content']['tmp_name']));

	try { $document->save(); }
	catch (Exception $e) { $_SESSION['errorMessages'][] = $e; }

	Header("Location: viewDocument.php?document_id={$document->getId()}");
?>