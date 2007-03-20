<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET department_id
 */
 	verifyUser();
	$department_id = isset($_GET['department_id']) ? $_GET['department_id'] : $_SESSION['USER']->getDepartment_id();

	if (isset($_FILES['image']))
	{
		$image = new Image();
		$image->setTitle($_POST['image']['title']);
		$image->setDescription($_POST['image']['description']);

		try
		{
			$image->setFile($_FILES['image']);
			$image->save();
		}
		catch(Exception $e) { $_SESSION['errorMessages'][] = $e; }
	}

	$template = new Template('imageBrowser');

	$images = new ImageList(array('department_id'=>$department_id));
	$department = new Department($department_id);
	$template->blocks[] = new Block('media/thumbnails.inc',array('imageList'=>$images,'department'=>$department));

	$template->blocks[] = new Block('media/addImageForm.inc');


	$template->render();
?>