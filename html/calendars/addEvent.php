<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET calendar_id
 */
	verifyUser(array('Administrator','Webmaster','Content Creator'));

	if (isset($_POST['event']))
	{
		# Start and End times are going to come in as strings
		# They need to be converted to date arrays before setting
		if (isset($_POST['allDayEvent']))
		{
			$_POST['event']['allDayEvent'] = 1;
			$_POST['startTime'] = '';
			$_POST['endTime'] = '';
		}
		$_POST['event']['start'] = getdate(strtotime(implode(' ',array($_POST['startDate'],$_POST['startTime']))));
		$_POST['event']['end'] = getdate(strtotime(implode(' ',array($_POST['endDate'],$_POST['endTime']))));

		$event = new Event();
		foreach($_POST['event'] as $field=>$value)
		{

			$set = 'set'.ucfirst($field);
			$event->$set($value);
		}

		try
		{
			$event->save();
			Header('Location: home.php');
			exit();
		}
		catch(Exception $e) { $_SESSION['errorMessages'][] = $e; }
	}

	$template = new Template('backend');
	$form = new Block('calendars/addEventForm.inc');
	if (isset($_GET['calendar_id'])) { $form->calendar_id = $_GET['calendar_id']; }
	$template->blocks[] = $form;
	$template->render();
?>