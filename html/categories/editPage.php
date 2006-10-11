<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
/*
	$_GET variables:	category_id
*/
	verifyUser('Administrator');

	$template = new Template("transitional");
	if (isset($_GET['category_id'])) { $category = new Category($_GET['category_id']); }
	if (isset($_POST['content']))
	{
		$category = new Category($_POST['id']);
		$category->setContent($_POST['content']);

		try
		{
			$category->save();
			Header("Location: viewCategory.php?category_id={$category->getId()}");
			exit();
		}
		catch (Exception $e) { $_SESSION['errorMessages'][] = $e; }
	}

	$FCKeditor = new FCKeditor("content");
	$FCKeditor->BasePath = BASE_URL."/FCKeditor/";
	$FCKeditor->ToolbarSet = 'Custom';
	$FCKeditor->Value = $category->getContent();

	$template->blocks[] = new Block("categories/editPageForm.inc",array('category'=>$category,'FCKeditor'=>$FCKeditor));
	$template->render();
?>