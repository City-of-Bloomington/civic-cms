<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
/*
	$_GET variables:	section_id
*/
	verifyUser('Publisher');
	if (isset($_GET['section_id']))
	{
		$section = new Section($_GET['section_id']);
		if (!$_SESSION['USER']->canEdit($section))
		{
			$_SESSION['errorMessages'][] = "noAccessAllowed";
			Header("Location: viewSection.php?section_id={$section->getId()}");
			exit();
		}
	}
	if (isset($_POST['content']))
	{
		$section = new Section($_POST['id']);
		if (!$_SESSION['USER']->canEdit($section))
		{
			$_SESSION['errorMessages'][] = "noAccessAllowed";
			Header("Location: viewSection.php?section_id={$section->getId()}");
			exit();
		}

		$section->getDocument()->setContent($_POST['content']);

		try
		{
			$section->getDocument()->save();
			Header("Location: viewSection.php?section_id={$section->getId()}");
			exit();
		}
		catch (Exception $e) { $_SESSION['errorMessages'][] = $e; }
	}

	$FCKeditor = new FCKeditor("content");
	$FCKeditor->BasePath = BASE_URL."/FCKeditor/";
	$FCKeditor->ToolbarSet = 'Custom';
	$FCKeditor->Value = $section->getDocument()->getContent();

	$template = new Template("transitional");
	$template->blocks[] = new Block("sections/editPageForm.inc",array('section'=>$section,'FCKeditor'=>$FCKeditor));
	$template->render();
?>