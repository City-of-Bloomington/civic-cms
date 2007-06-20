<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET section_id
 *
 * Section Navigation through the site should be handled by this script.
 */
	$section = new Section($_GET['section_id']);

	$_GET['document_id'] = $section->getDocument_id();
	include APPLICATION_HOME.'/html/documents/viewDocument.php';
?>