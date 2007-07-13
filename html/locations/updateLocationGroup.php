<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
	verifyUser(array('Administrator','Webmaster'));

	if (isset($_GET['id'])) { $locationGroup = new LocationGroup($_GET['id']); }
	if (isset($_POST['id']))
	{
		$locationGroup = new LocationGroup($_POST['id']);
		foreach($_POST['locationGroup'] as $field=>$value)
		{
			$set = 'set'.ucfirst($field);
			$locationGroup->$set($value);
		}

		try
		{
			$locationGroup->save();
			Header('Location: home.php');
			exit();
		}
		catch (Exception $e) { $_SESSION['errorMessages'][] = $e; }
	}

	$template = new Template();
	$template->blocks[] = new Block('locations/updateLocationGroupForm.inc',array('locationGroup'=>$locationGroup));
	$template->render();
?>