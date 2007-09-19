<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET tag_id
 */
	verifyUser('Webmaster');

	if (isset($_GET['tag_id'])) { $tag = new Tag($_GET['tag_id']); }
	if (isset($_POST['tag_id']))
	{
		$tag = new Tag($_POST['tag_id']);
		foreach($_POST['tag'] as $field=>$value)
		{
			$set = 'set'.ucfirst($field);
			$tag->$set($value);
		}
		$tag->setDescription($_POST['description']);

		try
		{
			$tag->save();
			Header("Location: home.php");
			exit();
		}
		catch (Exception $e) { $_SESSION['errorMessages'][] = $e; }
	}

	$template = new Template();
	$template->blocks[] = new Block('tags/updateTagForm.inc',array('tag'=>$tag));
	$template->render();
?>
