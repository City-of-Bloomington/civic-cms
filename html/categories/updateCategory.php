<?php
/*
	$_GET variables:	category_id
*/
	verifyUser('Administrator');

	$template = new Template();
	$form = new Block("categories/updateCategoryForm.inc");
	if (isset($_GET['category_id'])) { $form->category = new Category($_GET['category_id']); }

	if (isset($_POST['category']))
	{
		$category = new Category($_POST['category_id']);
		foreach($_POST['category'] as $field=>$value)
		{
			$set = "set".ucfirst($field);
			$category->$set($value);

			try
			{
				$category->save();
				Header("Location: home.php");
				exit();
			}
			catch (Exception $e)
			{
				$_SESSION['errorMessages'][] = $e;
				$form->category = $category;
			}
		}
	}

	$template->blocks[] = $form;
	$template->render();
?>