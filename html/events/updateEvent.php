<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET event_id
 */
	verifyUser(array('Webmaster','Administrator','Content Creator'));

	# Load the Event into the session
	if (isset($_GET['event_id'])) { $_SESSION['event'] = new Event($_GET['event_id']); }

	# Make sure they're allowed to edit the event
	if (!$_SESSION['event']->permitsEditingBy($_SESSION['USER']))
	{
		$_SESSION['errorMessages'][] = "noAccessAllowed";
		$template = new Template('closePopup');
		$template->render();
		exit();
	}

	# Handle any data that's posted
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
		if (isset($_POST['startDate']))
		{
			$_POST['event']['start'] = getdate(strtotime(implode(' ',array($_POST['startDate'],$_POST['startTime']))));
			$_POST['event']['end'] = getdate(strtotime(implode(' ',array($_POST['endDate'],$_POST['endTime']))));
		}

		# Choosing from the Full User Contact list should override
		# a selection from the short list
		if (isset($_POST['contact_id']) && $_POST['contact_id']) { $_POST['event']['contact_id'] = $_POST['contact_id']; }

		# Run the setters for all the POST fields
		foreach($_POST['event'] as $field=>$value)
		{
			$set = 'set'.ucfirst($field);
			$_SESSION['event']->$set($value);
		}
	}

	# Save the Event only when they ask for it
	if (isset($_POST['action']) && $_POST['action']=='save')
	{
		try
		{
			$_SESSION['event']->save();
			unset($_SESSION['event']);
			$template = new Template('closePopup');
			$template->render();
			exit();
		}
		catch (Exception $e) { $_SESSION['errorMessages'][] = $e; }
	}

	# Figure out which tab to show
	$tab = isset($_REQUEST['tab']) ? $_REQUEST['tab'] : 'info';
	$template = new Template('popup');
	$template->blocks[] = new Block('events/update/tabs.inc');
	$form = new Block("events/update/$tab.inc",array('event'=>$_SESSION['event']));

	# Handle any extra data the current tab needs


	$template->blocks[] = $form;
	$template->render();
?>