<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET event_id
 */
	$event = new Event($_GET['event_id']);

	$date = $event->dateStringToArray($event->getStart());
	$url = new URL(BASE_URL."/calendars");
	$url->parameters = array('year'=>$date['year'],'mon'=>$date['mon'],'mday'=>$date['mday']);

	$calendar = $event->getCalendar();

	$template = isset($_SESSION['USER']) ? new Template('backend') : new Template();
	$template->blocks[] = new Block('calendars/viewButtons.inc',array('url'=>$url,'calendar'=>$calendar));
	$template->blocks[] = new Block('calendars/viewEvent.inc',array('event'=>$event));
	$template->render();
?>