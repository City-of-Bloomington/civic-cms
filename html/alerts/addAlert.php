<?php
/**
 * @copyright Copyright (C) 2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
verifyUser(array('Administrator','Webmaster'));

if (isset($_POST['alert']))
{
	$alert = new Alert();
	$alert->setTitle($_POST['alert']['title']);
	$alert->setURL($_POST['alert']['url']);
	$alert->setText($_POST['alert']['text']);
	$alert->setStartTime("{$_POST['start']['date']} {$_POST['start']['time']}");
	$alert->setEndTime("{$_POST['end']['date']} {$_POST['end']['time']}");

	try
	{
		$alert->save();
		Header('Location: '.BASE_URL.'/alerts');
		exit();
	}
	catch(Exception $e) { $_SESSION['errorMessages'][] = $e; }
}

$template = new Template('backend');
$template->blocks[] = new Block('alerts/addAlertForm.inc');
echo $template->render();