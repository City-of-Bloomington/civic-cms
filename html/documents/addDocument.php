<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
/*
	$_GET variables:	section_id
	-------------------------------------------------------
	$_POST variables:	section_id
						content
*/
	verifyUser(array('Publisher','Content Creator'));

	if (isset($_GET['section_id']))
	{
		$section = new Section($_GET['section_id']);

		if (!$_SESSION['USER']->canEdit($section))
		{
			$_SESSION['errorMessages'][] = "noAccessAllowed";
			Header("Location: ".BASE_URL."/sections/viewSection.php?section_id={$section->getId()}");
			exit();
		}
	}

	if (isset($_POST['section_id']))
	{
		$section = new Section($_POST['section_id']);

		if (!$_SESSION['USER']->canEdit($section))
		{
			$_SESSION['errorMessages'][] = "noAccessAllowed";
			Header("Location: ".BASE_URL."/sections/viewSection.php?section_id={$section->getId()}");
			exit();
		}

		$document = new Document();
		$document->setContent($_POST['content']);
		$document->addSection($section);
		try
		{
			$document->save();
			Header("Location: ".BASE_URL."/sections/viewSection.php?section_id={$section->getId()}");
			exit();
		}
		catch (Exception $e) { $_SESSION['errorMessages'][] = $e; }
	}

	$FCKeditor = new FCKeditor("content");
	$FCKeditor->BasePath = BASE_URL."/FCKeditor/";
	$FCKeditor->ToolbarSet = 'Custom';
	if (isset($document)) { $FCKeditor->Value = $document->getContent(); }

	$template = new Template("transitional");
	$form = new Block('documents/addDocumentForm.inc',array('section'=>$section,'FCKeditor'=>$FCKeditor));
	$template->blocks[] = $form;
	$template->render();
?>