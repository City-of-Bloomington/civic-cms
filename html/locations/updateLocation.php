<?php
/**
 * @copyright 2006-2009 City of Bloomington, Indiana
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET return_url
 */
verifyUser(array('Administrator','Webmaster','Content Creator'));

if (isset($_REQUEST['location_id'])) {
	$location = new Location($_REQUEST['location_id']);

	# Make sure they're allowed to edit this Location
	if (!$location->permitsEditingBy($_SESSION['USER'])) {
		$_SESSION['errorMessages'][] = new Exception('noAccessAllowed');
		header('Location: home.php');
		exit();
	}
}
else {
	# We're creating a new Location
	$location = new Location();
}


if (isset($_POST['location'])) {
	# Make sure they're allowed to edit this location
	if (!$location->permitsEditingBy($_SESSION['USER'])) {
		$_SESSION['errorMessages'][] = new Exception('noAccessAllowed');
		header('Location: home.php');
		exit();
	}

	foreach ($_POST['location'] as $field=>$value) {
		$set = 'set'.ucfirst($field);
		$location->$set($value);
	}

	// Departments should only be changeable by Webmaster/Admin
	if (isset($_POST['department_id']) && userHasRole(array('Administrator','Webmaster'))) {
		$location->setDepartment_id($_POST['department_id']);
	}

	// Directions will come in from the WYSIWYG editor
	if (isset($_POST['content'])) {
		$location->setContent($_POST['content']);
	}

	try {
		$location->save();
		$facets = isset($_POST['facets']) ? $_POST['facets'] : array();
		$location->setFacets($facets);
		header("Location: $_POST[return_url]");
		exit();
	}
	catch (Exception $e) {
		$_SESSION['errorMessages'][] = $e;
	}
}

$form = new Block('locations/updateLocationForm.inc');
$form->location = $location;
$form->return_url = $_REQUEST['return_url'];

if ( !(userHasRole(array('Administrator','Webmaster'))) ) {
	$facetGroups = new FacetGroupList(array('department_id'=>$_SESSION['USER']->getDepartment_id()));
}
else  {
	$facetGroups = new FacetGroupList();
	$facetGroups->find();
}
$form->facetGroupList = $facetGroups;

$template = new Template();
$template->blocks[] = $form;
echo $template->render();
