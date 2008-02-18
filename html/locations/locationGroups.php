<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * Lists all the locationGroups.  This script was added so we'd have a controller
 * to provide this list as a web service.  For webservices, we want a separate list
 * for the LocationGroups, and a seperate list for the Locations
 */
	$template = isset($_GET['format']) ? new Template($_GET['format'],$_GET['format']) : new Template();

	$groupList = new LocationGroupList();
	$groupList->find();
	$template->blocks[] = new Block('locations/locationGroupList.inc',array('locationGroupList'=>$groupList));

	echo $template->render();
?>