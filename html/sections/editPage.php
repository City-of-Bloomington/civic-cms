<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
/*
	$_GET variables:	section_id
*/
	verifyUser('Administrator');

	$template = new Template("transitional");
	if (isset($_GET['section_id'])) { $section = new Section($_GET['section_id']); }
	if (isset($_POST['content']))
	{
		$section = new Section($_POST['id']);
		$section->setContent($_POST['content']);

		try
		{
			$section->save();
			Header("Location: viewSection.php?section_id={$section->getId()}");
			exit();
		}
		catch (Exception $e) { $_SESSION['errorMessages'][] = $e; }
	}

	$FCKeditor = new FCKeditor("content");
	$FCKeditor->BasePath = BASE_URL."/FCKeditor/";
	$FCKeditor->ToolbarSet = 'Custom';
	$FCKeditor->Value = $section->getContent();

	$template->blocks[] = new Block("sections/editPageForm.inc",array('section'=>$section,'FCKeditor'=>$FCKeditor));
	$template->render();
?>