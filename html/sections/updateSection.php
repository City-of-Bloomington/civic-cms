<?php
/*
	$_GET variables:	section_id
*/
	verifyUser('Administrator');

	$template = new Template();
	$form = new Block("sections/updateSectionForm.inc");
	if (isset($_GET['section_id'])) { $form->section = new Section($_GET['section_id']); }

	if (isset($_POST['section']))
	{
		$section = new Section($_POST['id']);
		foreach($_POST['section'] as $field=>$value)
		{
			$set = "set".ucfirst($field);
			$section->$set($value);
		}

		try
		{
			$section->save();
			Header("Location: home.php");
			exit();
		}
		catch (Exception $e)
		{
			$_SESSION['errorMessages'][] = $e;
			$form->section = $section;
		}
	}

	$template->blocks[] = $form;
	$template->render();
?>