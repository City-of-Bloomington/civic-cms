<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
/*
	$_GET variables:	document_id
*/
	$document = new Document($_GET['document_id']);
	$document->removeWatch($_SESSION['USER']);
	Header("Location: viewDocument.php?document_id={$document->getId()}");
?>