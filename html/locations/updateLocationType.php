<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
	verifyUser(array('Administrator','Webmaster'));

	if (isset($_GET['id'])) { $locationType = new LocationType($_GET['id']); }
	if (isset($_POST['id']))
	{
		$locationType = new LocationType($_POST['id']);
		foreach($_POST['locationType'] as $field=>$value)
		{
			$set = 'set'.ucfirst($field);
			$locationType->$set($value);
		}

		try
		{
			$locationType->save();
			Header('Location: home.php');
			exit();
		}
		catch (Exception $e) { $_SESSION['errorMessages'][] = $e; }
	}

	$template = new Template();
	$template->blocks[] = new Block('locations/updateLocationTypeForm.inc',array('locationType'=>$locationType));
	$template->render();
?>