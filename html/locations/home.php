<?php
/**
 * @copyright 2006-2009 City of Bloomington, Indiana
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET locationGroup_id
 */
$format = isset($_GET['format']) ? strtolower($_GET['format']) : 'html';
switch($format) {
	case 'html':
		$template = new Template('backend');

		#Load the default locationGroup, if they didn't choose one
		if (!isset($_GET['locationGroup_id'])) {
			$list = new LocationGroupList(array('default'=>true));
			if (count($list)) {
				$_GET['locationGroup_id'] = $list[0]->getId();
			}
		}
		break;
	default:
		$template = new Template('default',$_GET['format']);
}

$listBlock = new Block('locations/locationList.inc');
if (isset($_GET['locationGroup_id']) && is_numeric($_GET['locationGroup_id'])) {
	if ($_GET['locationGroup_id'] > 0) {
		try {
			$group = new LocationGroup($_GET['locationGroup_id']);
			$fields['locationGroup_id'] = $group->getId();
			$listBlock->title = $group->getName();
			$listBlock->locationGroup = $group;
		}
		catch (Exception $e) {
			$_SESSION['errorMessages'][] = $e;
		}
	}
	else {
		$fields['locationGroup_id'] = null;
		$listBlock->title = 'Other';
	}


	# The user can ask for the list to be sorted by distance from a given point
	if (isset($_GET['latitude']) && isset($_GET['longitude'])) {
		$sort = 'distance';
		$fields['latitude'] = $_GET['latitude'];
		$fields['longitude'] = $_GET['longitude'];
		if (isset($_GET['limit'])) {
			$limit = (int)$_GET['limit'];
		}
	}
	else {
		$sort = 'name';
	}


	# Don't bother trying to look anything up if we don't have a valid group
	if (isset($fields)) {
		$limit = isset($limit) ? $limit : null;
		$locationList = new LocationList();
		$locationList->find($fields,$sort,$limit);
		$listBlock->locationList = $locationList;
	}
}
else {
	$listBlock->title = 'Locations';

	# If they ask for data from a service without specifying a particular group,
	# send them a file with all the groups
	$listBlock = new Block('locations/locationGroupList.inc');
}


# Include blocks for editing Location Groups
if ($template->outputFormat==='html') {
	# If we have a locationGroup, include it in the breadcrumbs
	$breadcrumbs = new Block('locations/breadcrumbs.inc');
	if (isset($group)) {
		$breadcrumbs->locationGroup = $group;
	}
	$template->blocks[] = $breadcrumbs;

	if (userHasRole(array('Administrator','Webmaster'))) {
		$typeList = new LocationTypeList();
		$typeList->find();
		$template->blocks[] = new Block('locations/locationTypeList.inc',
										array('locationTypeList'=>$typeList));

		$groupList = new LocationGroupList();
		$groupList->find();
		$template->blocks[] = new Block('locations/locationGroupList.inc',
										array('locationGroupList'=>$groupList));
	}
}

$template->blocks[] = $listBlock;
echo $template->render();
