<?php
/**
 * @copyright Copyright (C) 2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET language_id
 */
verifyUser('Administrator');

$language = new Language($_REQUEST['language_id']);
if (isset($_POST['language']))
{
	foreach($_POST['language'] as $field=>$value)
	{
		$set = 'set'.ucfirst($field);
		$language->$set($value);
	}

	try
	{
		$language->save();
		Header('Location: index.php');
		exit();
	}
	catch(Exception $e) { $_SESSION['errorMessages'][] = $e; }
}

$template = new Template();
$template->blocks[] = new Block('languages/updateLanguageForm.inc',array('language'=>$language));
echo $template->render();