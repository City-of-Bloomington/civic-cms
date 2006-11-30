<?php
	verifyUser("Webmaster");

	$template = new Template();
	$template->blocks[] = new Block("sections/addSectionForm.inc");
	if (isset($_POST['section']))
	{
		$section = new Section();
		foreach($_POST['section'] as $field=>$value)
		{
			$set = "set".ucfirst($field);
			$section->$set($value);
		}

		try { $section->save(); }
		catch (Exception $e)
		{
			$_SESSION['errorMessages'][] = $e;
			print_r($e);
			exit();
		}
	}
	$template->render();
?>