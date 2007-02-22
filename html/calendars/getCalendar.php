<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
/*
	Outputs the calendar in iCal format
*/
	if (isset($_GET['calendar_id'])) { $calendar = new Calendar($_GET['calendar_id']); }
	else { $calendar = new Calendar(); }

	$template = new Template('ical',array('calendar'=>$calendar));
	$template->blocks[] = new Block('calendars/ical.inc',array('calendar'=>$calendar));
	$template->render();
?>