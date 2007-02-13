<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
	verifyUser('Webmaster');
	$calendarList = new CalendarList();
	$calendarList->find();

	$template = new Template();
	$template->blocks[] = new Block('calendars/calendarList.inc',array('calendarList'=>$calendarList));
	$template->render();
?>