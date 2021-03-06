<?php
/**
 * @copyright 2006-2010 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET event_id
 * @param GET date (optional) A date in the form of Y-m-d
 */
if (!isset($_GET['event_id']) || !$_GET['event_id']) {
	header('Location: home.php');
	exit();
}

try {
	$event = new Event($_GET['event_id']);
}
catch (Exception $e) {
	$_SESSION['errorMessages'][] = $e;
	header('Location: home.php');
	exit();
}

$date = getdate($event->getStart());
$url = new URL(BASE_URL."/calendars");
$url->parameters = array('year'=>$date['year'],'mon'=>$date['mon'],'mday'=>$date['mday']);

$calendar = $event->getCalendar();

$template = isset($_GET['format']) ? new Template('default',$_GET['format']) : new Template();
if ($template->outputFormat == 'html') {
	$template->blocks[] = new Block('calendars/breadcrumbs.inc',array('event'=>$event));
	$template->blocks[] = new Block('calendars/viewButtons.inc',
									array('url'=>$url,'calendar'=>$calendar));
}


// If a specific date is requested, load the first recurrence
// of that event for that date
if (isset($_GET['date'])) {
	$rangeStart = strtotime($_GET['date']);
	$rangeEnd = strtotime('+1 day',$rangeStart);

	$recurrences = $event->getRecurrences($rangeStart,$rangeEnd);
	if (count($recurrences)) {
		$event = $recurrences[0];
	}
	else {
		$_SESSION['errorMessages'][] = new Exception('events/unknownRecurrence');
	}
}
$template->blocks[] = new Block('events/viewEvent.inc',array('event'=>$event));
echo $template->render();

