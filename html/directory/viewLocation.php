<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET category
 * @param GET department
 * @param GET location
 */
	$template = new Template();

	$breadcrumbs = new Block('directory/breadcrumbs.inc');
	$breadcrumbs->category = $_GET['category'];
	$breadcrumbs->department = $_GET['department'];
	$breadcrumbs->location = $_GET['location'];
	$template->blocks[] = $breadcrumbs;

	$locationBlock = new Block('directory/viewLocation.inc');
	$locationBlock->category = $_GET['category'];
	$locationBlock->department = $_GET['department'];
	$locationBlock->location = $_GET['location'];
	$template->blocks[] = $locationBlock;

	echo $template->render();
?>