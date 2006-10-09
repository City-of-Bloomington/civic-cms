<?php
	verifyUser("Administrator");

	$template = new Template();
	$template->blocks[] = new Block("categories/addCategoryForm.inc");
	if (isset($_POST['category']))
	{
		$category = new Category();
		foreach($_POST['category'] as $field=>$value)
		{
			$set = "set".ucfirst($field);
			$category->$set($value);
		}

		try { $category->save(); }
		catch (Exception $e) { $_SESSION['errorMessages'][] = $e; }
	}
	$template->render();
?>