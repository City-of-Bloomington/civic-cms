<?php
/**
 * @copyright Copyright (C) 2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
verifyUser('Administrator');

if (isset($_POST['language']))
{
	$language = new Language();
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
$template->blocks[] = new Block('languages/addLanguageForm.inc');
echo $template->render();