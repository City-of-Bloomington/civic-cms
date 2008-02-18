<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET event_id
 * @param GET date (optional) A date in the form of Y-m-d
 */
$event = new Event($_GET['event_id']);

$date = getdate($event->getStart());
$url = new URL(BASE_URL."/calendars");
$url->parameters = array('year'=>$date['year'],'mon'=>$date['mon'],'mday'=>$date['mday']);

$calendar = $event->getCalendar();

$template = new Template();
$template->blocks[] = new Block('calendars/breadcrumbs.inc',array('event'=>$event));
$template->blocks[] = new Block('calendars/viewButtons.inc',array('url'=>$url,'calendar'=>$calendar));


# If a specific date is requested, load the first recurrence
# of that event for that date
if (isset($_GET['date']))
{
	$rangeStart = strtotime($_GET['date']);
	$rangeEnd = strtotime('+1 day',$rangeStart);

	$recurrences = $event->getRecurrences($rangeStart,$rangeEnd);
	if (count($recurrences))
	{
		$event = $recurrences[0];
	}
	else { $_SESSION['errorMessages'][] = new Exception('events/unknownRecurrence'); }
}
$template->blocks[] = new Block('events/viewEvent.inc',array('event'=>$event));
echo $template->render();
