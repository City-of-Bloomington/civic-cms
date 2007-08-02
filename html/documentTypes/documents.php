<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET documentType_id
 *
 * Displays the documents of a given DocumentType, organized by Facet
 */
	$type = new DocumentType($_GET['documentType_id']);

	$template = new Template();
	$template->blocks[] = new Block('documentTypes/documents.inc',array('documentType'=>$type));
	$template->render();
?>