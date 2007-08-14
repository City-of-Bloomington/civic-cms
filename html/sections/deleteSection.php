<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET section_id
 */
	verifyUser(array('Administrator','Webmaster'));

	$section = new Section($_GET['section_id']);
	try { $section->delete(); }
	catch (Exception $e) { $_SESSION['errorMessages'][] = $e; }

	Header('Location: '.BASE_URL.'/sections');
?>