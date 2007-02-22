<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
	verifyUser(array('Administrator','Webmaster','Content Creator'));

	if (isset($_GET['event_id'])) { $event = new Event($_GET['event_id']); }
	if (isset($_POST['event_id']))
	{
		$event = new Event($_POST['event_id']);
		foreach($_POST['event'] as $field=>$value)
		{
			$set = 'set'.ucfirst($field);
			$event->$set($value);
		}

		try
		{
			$event->save();
			Header('Location: viewEvent.php?event_id='.$event->getId());
			exit();
		}
		catch (Exception $e) { $_SESSION['errorMessages'][] = $e; }
	}

	$template = new Template('backend');
	$template->blocks[] = new Block('calendars/updateEventForm.inc',array('event'=>$event));
	$template->render();
?>