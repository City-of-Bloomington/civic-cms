<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
	verifyUser('Webmaster');

	$locationList = new LocationList();
	$locationList->find();

	$template = new Template('backend');
	$template->blocks[] = new Block('locations/locationList.inc',array('locationList'=>$locationList));
	$template->render();
?>