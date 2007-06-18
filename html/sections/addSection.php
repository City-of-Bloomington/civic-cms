<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
	verifyUser("Webmaster");

	if (isset($_POST['section']))
	{
		$section = new Section();
		foreach($_POST['section'] as $field=>$value)
		{
			$set = "set".ucfirst($field);
			$section->$set($value);
		}

		try
		{
			$section->save();
			Header("Location: sectionInfo.php?section_id={$section->getId()}");
			exit();
		}
		catch (Exception $e) { $_SESSION['errorMessages'][] = $e; }
	}
	$template = new Template();
	$template->blocks[] = new Block("sections/addSectionForm.inc");
	$template->render();
?>