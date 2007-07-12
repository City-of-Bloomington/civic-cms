<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
	verifyUser('Webmaster');

	$template = new Template();

	$typeList = new LocationTypeList();
	$typeList->find();
	$template->blocks[] = new Block('locations/locationTypeList.inc',array('locationTypeList'=>$typeList));

	$locationList = new LocationList();
	$locationList->find();
	$template->blocks[] = new Block('locations/locationList.inc',array('locationList'=>$locationList));

	$template->render();
?>