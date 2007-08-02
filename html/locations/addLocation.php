<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
	verifyUser(array('Administrator','Webmaster','Content Creator'));

	if (isset($_POST['location']))
	{
		$location = new Location();
		foreach($_POST['location'] as $field=>$value)
		{
			$set = 'set'.ucfirst($field);
			$location->$set($value);
		}

		# Departments should only be changeable by Webmaster/Admin
		if (isset($_POST['department_id']) && userHasRole(array('Administrator','Webmaster')))
		{
			$location->setDepartment_id($_POST['department_id']);
		}
		else { $location->setDepartment_id($_SESSION['USER']->getDepartment_id()); }

		# Directions will come in from the WYSIWYG editor
		if (isset($_POST['directions'])) { $location->setDirections($_POST['directions']); }

		try
		{
			$location->save();
			Header('Location: home.php');
			exit();
		}
		catch(Exception $e) { $_SESSION['errorMessages'][] = $e; }
	}

	$template = new Template();
	$template->blocks[] = new Block('locations/addLocationForm.inc');
	$template->render();
?>