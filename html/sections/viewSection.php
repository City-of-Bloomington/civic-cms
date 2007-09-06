<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET section_id
 *
 * Section Navigation through the site should be handled by this script.
 */
 	try
 	{
 		$section = new Section($_GET['section_id']);
		if ($section->getDocument_id()) { $_GET['document_id'] = $section->getDocument_id(); }
		else { throw new Exception('sections/missingHomeDocument'); }
 	}
 	catch(Exception $e) { $_SESSION['errorMessages'][] = $e; }

	# make sure we've got a section homepage

	include APPLICATION_HOME.'/html/documents/viewDocument.php';
?>