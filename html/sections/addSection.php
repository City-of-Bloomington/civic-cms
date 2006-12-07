<?php
	verifyUser("Webmaster");

	if (isset($_POST['section']))
	{
		$section = new Section();
		foreach($_POST['section'] as $field=>$value)
		{
			$set = "set".ucfirst($field);
			$section->$set($value);
		}

		try { $section->save(); }
		catch (Exception $e) { $_SESSION['errorMessages'][] = $e; }
	}
	$template = new Template();
	$template->blocks[] = new Block("sections/addSectionForm.inc");
	$template->render();
?>