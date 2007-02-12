<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
	verifyUser('Administrator');

	if (isset($_POST['department']))
	{
		$department = new Department();
		$department->setName($_POST['department']['name']);

		try
		{
			$department->save();
			Header("Location: home.php");
			exit();
		}
		catch (Exception $e) { $_SESSION['errorMessages'][] = $e; }
	}

	$template = new Template('backend');
	$template->blocks[] = new Block('departments/addDepartmentForm.inc');
	$template->render();
?>