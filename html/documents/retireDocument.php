<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
/*
	$_GET variables:	document_id
*/
	verifyUser(array('Administrator','Webmaster','Content Creator'));
	$document = new Document($_GET['document_id']);

	if ($document->permitsEditingBy($_SESSION['USER']))
	{
		$document->setRetireDate(getdate());
		try { $document->save(); }
		catch (Exception $e) { $_SESSION['errorMessages'][] = $e; }
	}

	Header('Location: myDocuments.php');
?>