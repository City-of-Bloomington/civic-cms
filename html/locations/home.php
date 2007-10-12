<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET locationGroup_id
 */
	$format = isset($_GET['format']) ? strtolower($_GET['format']) : 'html';
	switch($format)
	{
		case 'html': $template = new Template('backend'); break;
		default: $template = new Template($_GET['format'],$_GET['format']);
	}

	$listBlock = new Block('locations/locationList.inc');
	if (isset($_GET['locationGroup_id']) && is_numeric($_GET['locationGroup_id']))
	{
		if ($_GET['locationGroup_id']>0)
		{
			$group = new LocationGroup($_GET['locationGroup_id']);
			$fields['locationGroup_id'] = $group->getId();
			$listBlock->title = $group->getName();
			$listBlock->locationGroup = $group;
		}
		else
		{
			$fields['locationGroup_id'] = null;
			$listBlock->title = 'Other';
		}


		if (isset($_GET['sort']) && isset($_GET['latitude']) && isset($_GET['longitude']))
		{
			$sort = 'distance';
			$fields['latitude'] = $_GET['latitude'];
			$fields['longitude'] = $_GET['longitude'];
		}
		else { $sort = 'name'; }

		$listBlock->locationList = new LocationList($fields,$sort);
	}
	else
	{
		$listBlock->title = 'Locations';
	}


	if ($template->outputFormat==='html')
	{
		# If we have a locationGroup, include it in the breadcrumbs
		$breadcrumbs = new Block('locations/breadcrumbs.inc');
		if (isset($group)) { $breadcrumbs->locationGroup = $group; }
		$template->blocks[] = $breadcrumbs;

		if (userHasRole(array('Administrator','Webmaster')))
		{
			$typeList = new LocationTypeList();
			$typeList->find();
			$template->blocks[] = new Block('locations/locationTypeList.inc',array('locationTypeList'=>$typeList));

			$groupList = new LocationGroupList();
			$groupList->find();
			$template->blocks[] = new Block('locations/locationGroupList.inc',array('locationGroupList'=>$groupList));
		}
	}





	$template->blocks[] = $listBlock;



	$template->render();
?>
