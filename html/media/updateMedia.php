<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET media_id
 */
 	verifyUser();
 	$media = new Media($_REQUEST['media_id']);
 	if (!$media->permitsEditingBy($_SESSION['USER']))
 	{
 		$_SESSION['errorMessages'][] = new Exception('noAccessAllowed');
		Header('Location: '.BASE_URL.'/media');
		exit();
 	}

 	if (isset($_POST['media']))
 	{
 		foreach($_POST['media'] as $field=>$value)
 		{
 			$set = 'set'.ucfirst($field);
 			$media->$set($value);
 		}

 		try
 		{
	 		if (isset($_FILES['upload']) && is_uploaded_file($_FILES['upload']['tmp_name']))
	 		{
	 			$media->setFile($_FILES['upload']);
	 		}
 			$media->save();
 			header('Location: info.php?media_id='.$media->getId());
 			exit();
 		}
 		catch (Exception $e) { $_SESSION['errorMessages'][] = $e; }
 	}

 	$template = new Template('backend');
 	$template->blocks[] = new Block('media/updateMediaForm.inc',array('media'=>$media));
 	echo $template->render();
?>