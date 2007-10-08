<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET location_id
 */
	$location = new Location($_GET['location_id']);

	$template = new Template();
	$template->blocks[] = new Block('locations/breadcrumbs.inc',array('location'=>$location));
	$template->blocks[] = new Block('locations/viewLocation.inc',array('location'=>$location));
	$template->render();
?>