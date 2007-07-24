<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET locationGroup_id
 */
	$template = new Template();

	if (userHasRole(array('Administrator','Webmaster')))
	{
		$typeList = new LocationTypeList();
		$typeList->find();
		$template->blocks[] = new Block('locations/locationTypeList.inc',array('locationTypeList'=>$typeList));

		$groupList = new LocationGroupList();
		$groupList->find();
		$template->blocks[] = new Block('locations/locationGroupList.inc',array('locationGroupList'=>$groupList));
	}


	$listBlock = new Block('locations/locationList.inc');
	if (isset($_GET['locationGroup_id']) && is_numeric($_GET['locationGroup_id']))
	{
		$listBlock->locationGroup = new LocationGroup($_GET['locationGroup_id']);
	}
	$template->blocks[] = $listBlock;


	$template->render();
?>