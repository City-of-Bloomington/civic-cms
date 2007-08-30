<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
	verifyUser(array('Administrator','Webmaster','Content Creator'));

	# Create the new, empty Event
	if (!isset($_SESSION['event'])) { $_SESSION['event'] = new Event(); }

	# Handle any data that's posted
	if (isset($_POST['event']))
	{
		# Start and End times are going to come in as strings
		if (isset($_POST['allDayEvent']))
		{
			$_POST['event']['allDayEvent'] = 1;
			$_POST['startTime'] = '';
			$_POST['endTime'] = '';
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
	# Description comes in as HTML from the WYWSIWYG editor
	if (isset($_POST['description']))
	{
		$_SESSION['event']->setDescription($_POST['description']);
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
	$template->blocks[] = new Block('events/update/tabs.inc',array('currentTab'=>$tab));
	$form = new Block("events/update/$tab.inc",array('event'=>$_SESSION['event']));

	# Handle any extra data the current tab needs


	$template->blocks[] = $form;
	$template->render();
?>