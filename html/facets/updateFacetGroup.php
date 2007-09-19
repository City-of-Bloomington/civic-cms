<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET tagGroup_id
 */
	verifyUser(array('Administrator','Webmaster'));

	if (isset($_GET['tagGroup_id'])) { $tagGroup = new TagGroup($_GET['tagGroup_id']); }
	if (isset($_POST['tagGroup_id']))
	{
		$tagGroup = new TagGroup($_POST['tagGroup_id']);
		foreach($_POST['tagGroup'] as $field=>$value)
		{
			$set = 'set'.ucfirst($field);
			$tagGroup->$set($value);
		}

		try
		{
			$tagGroup->save();
			Header('Location: home.php');
			exit();
		}
		catch (Exception $e) { $_SESSION['errorMessages'][] = $e; }
	}

	$template = new Template();
	$template->blocks[] = new Block('tags/updateTagGroupForm.inc',array('tagGroup'=>$tagGroup));
	$template->render();
?>
