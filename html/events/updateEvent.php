<?php
/**
 * @copyright Copyright (C) 2007-2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET event_id
 */
	verifyUser(array('Webmaster','Administrator','Content Creator'));

	# Keep track of where to send them back to
	$return_url = isset($_REQUEST['return_url']) ? new URL($_REQUEST['return_url']) : new URL(BASE_URL.'/calendars');

	# We're keeping track of editing multiple events by instance_ic
	# instance_id must be passed in all the forms
	if (isset($_REQUEST['instance_id'])) { $instance_id = $_REQUEST['instance_id']; }
	else
	{
		# Create a new instance
		# If they pass an event_id then we're editing that event
		if (isset($_GET['event_id']))
		{
			$_SESSION['event'][] = new Event($_GET['event_id']);
			$keys = array_keys($_SESSION['event']);
			$instance_id = end($keys);
		}
		# We're creating a new event
		else
		{
			$_SESSION['event'][] = new Event();
			$keys = array_keys($_SESSION['event']);
			$instance_id = end($keys);

			if (isset($_GET['calendar_id']))
			{
				$_SESSION['event'][$instance_id]->setCalendar_id($_GET['calendar_id']);
			}
		}
	}

	# Make sure they're allowed to edit the event
	if (!$_SESSION['event'][$instance_id]->permitsEditingBy($_SESSION['USER']))
	{
		$_SESSION['errorMessages'][] = new Exception('events/noEditingAllowed');
		unset($_SESSION['event'][$instance_id]);
		header('Location: '.BASE_URL.'/calendars');
		exit();
	}

	# Handle any data that's posted
	if (isset($_POST['event']))
	{
		# Start and End times are going to come in as seperate strings
		if (isset($_POST['allDayEvent']))
		{
			$_SESSION['event'][$instance_id]->setAllDayEvent(1);
			$_POST['startTime'] = '';
			$_POST['endTime'] = '';
		}
		if (isset($_POST['startDate']))
		{
			$_SESSION['event'][$instance_id]->setStart("$_POST[startDate] $_POST[startTime]");
			$_SESSION['event'][$instance_id]->setEnd("$_POST[endDate] $_POST[endTime]");
		}

		# Parse all the RRULE stuff
		if (isset($_POST['freq']))
		{
			if ($_POST['freq'])
			{
				$_SESSION['event'][$instance_id]->setRrule_freq($_POST['freq']);
				switch($_SESSION['event'][$instance_id]->getRrule_freq())
				{
					case 'DAILY':
						$_SESSION['event'][$instance_id]->setRrule_interval($_POST['daily_interval']);
						break;
					case 'WEEKLY':
						$_SESSION['event'][$instance_id]->setRrule_interval($_POST['weekly_interval']);
						if (isset($_POST['weekly']['BYDAY']))
						{
							$byday = array();
							foreach($_POST['weekly']['BYDAY'] as $day=>$value)
							{
								$byday[] = $day;
							}
							$_SESSION['event'][$instance_id]->setRrule_byday(implode(',',$byday));
						}
						break;
					case 'MONTHLY':
						switch($_POST['monthly_type'])
						{
							case 'BYMONTHDAY':
								$_SESSION['event'][$instance_id]->setRrule_bymonthday($_POST['bymonthday']);
								$_SESSION['event'][$instance_id]->setRrule_interval($_POST['bymonthday_interval']);
								break;
							case 'BYDAY':
								$day = $_POST['offset'].$_POST['monthly_byday'];
								$_SESSION['event'][$instance_id]->setRrule_byday($day);
								$_SESSION['event'][$instance_id]->setRrule_interval($_POST['monthly_interval']);
								break;
						}
						break;
				}
				if ($_POST['rrule_end_type']=='count') { $_SESSION['event'][$instance_id]->setRrule_count($_POST['count']); }
				elseif($_POST['rrule_end_type']=='until') { $_SESSION['event'][$instance_id]->setRrule_until($_POST['until']); }
				else
				{
					$_SESSION['event'][$instance_id]->setRrule_count(null);
					$_SESSION['event'][$instance_id]->setRrule_until(null);
				}
			}
			else
			{
				# Clear out the RRULE
				$_SESSION['event'][$instance_id]->setRRule(null);
			}
		}

		# Choosing from the Full User Contact list should override
		# a selection from the short list
		if (isset($_POST['contact_id']) && $_POST['contact_id']) { $_POST['event']['contact_id'] = $_POST['contact_id']; }

		# Run the setters for all the POST fields
		foreach($_POST['event'] as $field=>$value)
		{
			$set = 'set'.ucfirst($field);
			$_SESSION['event'][$instance_id]->$set($value);
		}
	}
	# Description comes in as HTML from the WYWSIWYG editor
	if (isset($_POST['description']))
	{
		$_SESSION['event'][$instance_id]->setDescription($_POST['description']);
	}

	# Save the Event only when they ask for it
	if (isset($_POST['action']) && $_POST['action']=='save')
	{
		try
		{
			$_SESSION['event'][$instance_id]->save();
			unset($_SESSION['event'][$instance_id]);
			Header("Location: $return_url");
			exit();
		}
		catch (Exception $e) { $_SESSION['errorMessages'][] = $e; }
	}

	# Figure out which tab to show
	$currentTab = isset($_REQUEST['tab']) ? $_REQUEST['tab'] : 'info';
	$tabs = new Block('events/update/tabs.inc',array('currentTab'=>$currentTab));

	$form = new Block("events/update/$currentTab.inc");
	$form->event = $_SESSION['event'][$instance_id];
	$form->instance_id = $instance_id;
	$form->return_url = $return_url;

	$template = new Template('popup');
	$template->blocks[] = $tabs;
	$template->blocks[] = $form;
	echo $template->render();
