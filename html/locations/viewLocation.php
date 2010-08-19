<?php
/**
 * @copyright 2007-2010 City of Bloomington, Indiana
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET location_id
 */
$format = isset($_GET['format']) ? strtolower($_GET['format']) : 'html';
switch($format) {
	case 'print':
		$template = new Template('print','html');
		break;
	case 'contentonly':
		$template = new Template('contentonly','html');
		break;
	default:
		$template = new Template();
}

if (!isset($_GET['location_id']) || !$_GET['location_id']) {
	header('Location: '.BASE_URL.'/locations');
	exit();
}

try {
	$location = new Location($_GET['location_id']);
}
catch (Exception $e) {
	$_SESSION['errorMessages'][] = $e;
	header('Location: '.BASE_URL.'/locations');
	exit();
}

if ($template->outputFormat == 'html') {
	$template->blocks[] = new Block('locations/breadcrumbs.inc',array('location'=>$location));
}
$template->blocks[] = new Block('locations/viewLocation.inc',array('location'=>$location));
echo $template->render();
