<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
/*
	$_GET variables:	department_id
*/
	verifyUser('Administrator');

	if (isset($_GET['department_id'])) { $department = new Department($_GET['department_id']); }
	if (isset($_POST['department']))
	{
		$department = new Department($_POST['department_id']);
		try
		{
			foreach($_POST['department'] as $field=>$value)
			{
				$set = 'set'.ucfirst($field);
				$department->$set($value);
			}

			$department->save();
			Header("Location: home.php");
			exit();
		}
		catch (Exception $e) { $_SESSION['errorMessages'][] = $e; }
	}

	$template = new Template();
	$template->blocks[] = new Block('departments/updateDepartmentForm.inc',array('department'=>$department));
	$template->render();
?>