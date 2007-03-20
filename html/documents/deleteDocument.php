<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET document_id
 */
	verifyUser();

	$document = new Document($_GET['document_id']);

	if ($document->permitsEditingBy($_SESSION['USER']))
	{
		$document->delete();
	}

	#Header("Location: index.php");
?>