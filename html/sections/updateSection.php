<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET section_id
 */
	verifyUser(array('Administrator','Webmaster'));

	if (isset($_GET['section_id'])) { $section = new Section($_GET['section_id']); }
	if (isset($_POST['section']))
	{
		$section = new Section($_POST['id']);

		try
		{
			foreach($_POST['section'] as $field=>$value)
			{
				$set = "set".ucfirst($field);
				$section->$set($value);
			}
			$section->save();
			Header("Location: sectionInfo.php?section_id={$section->getId()}");
			exit();
		}
		catch (Exception $e) { $_SESSION['errorMessages'][] = $e; }
	}

	$template = new Template();
	$template->blocks[] = new Block('sections/updateSectionForm.inc',array('section'=>$section));
	$template->render();
?>