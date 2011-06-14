<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
	verifyUser(array('Administrator','Webmaster'));

	if (isset($_POST['locationType']))
	{
		$locationType = new LocationType();
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
		catch(Exception $e) { $_SESSION['errorMessages'][] = $e; }
	}

	$template = new Template();
	$template->blocks[] = new Block('locations/addLocationTypeForm.inc');
	echo $template->render();
?>