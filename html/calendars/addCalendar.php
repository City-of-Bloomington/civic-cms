<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
	verifyUser('Webmaster');

	if (isset($_POST['calendar']))
	{
		$calendar = new Calendar();
		foreach($_POST['calendar'] as $field=>$value)
		{
			$set = 'set'.ucfirst($field);
			$calendar->$set($value);
		}

		try
		{
			$calendar->save();
			Header('Location: home.php?calendar_id='.$calendar->getId());
			exit();
		}
		catch(Exception $e) { $_SESSION['errorMessages'][] = $e; }
	}

	$template = new Template();
	$template->blocks[] = new Block('calendars/addCalendarForm.inc');
	$template->render();
?>