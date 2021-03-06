<?php
/**
 * @copyright 2006-2012 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET calendar_id
 */
if (isset($_GET['calendar_id'])) {
	try {
		$calendar = new Calendar($_GET['calendar_id']);
	}
	catch (Exception $e) {
	}
}
if (!isset($calendar)) {
	$calendar = new Calendar();
}
$template = isset($_GET['format']) ? new Template('default',$_GET['format']) : new Template();

if ($template->outputFormat!='ical') {
	// Figure out which display we're going to use
	if (isset($_GET['view'])) {
		switch ($_GET['view']) {
			case 'month': $block = 'calendars/monthView.inc'; break;
			case 'list': $block = 'calendars/listView.inc'; break;
			case 'twoweek': $block = 'calendars/twoWeekView.inc'; break;
			case 'week': $block = 'calendars/weekView.inc'; break;
			case 'day': $block = 'calendars/dayView.inc'; break;
			default: $block = 'calendars/listView.inc';
		}
	}
	else {
		$block = 'calendars/monthView.inc';
	}

	// Get the date that we're wanting to display
	$now = getdate();
	if (isset($_GET['year']) || isset($_GET['mon']) || isset($_GET['mday'])) {
		$date['year'] = isset($_GET['year']) ? (int)$_GET['year'] : $now['year'];
		$date['mon'] = isset($_GET['mon']) ? (int)$_GET['mon'] : $now['mon'];
		$date['mday'] = isset($_GET['mday']) ? (int)$_GET['mday'] : $now['mday'];
	}
	else {
		$date = $now;
	}

	if ($template->outputFormat==='html') {
		$url = new URL($_SERVER['SERVER_NAME'].$_SERVER['REQUEST_URI']);
		$template->blocks[] = new Block('calendars/breadcrumbs.inc',array('calendar'=>$calendar));
		$template->blocks[] = new Block('calendars/viewButtons.inc',array('url'=>$url,'calendar'=>$calendar));
	}

	$template->blocks[] = new Block($block,array('calendar'=>$calendar,'date'=>$date));

	// Only show the event buttons if they can actually add an event
	if ($template->outputFormat==='html') {
		$addable = false;
		if (isset($_SESSION['USER'])) {
			$list = new CalendarList();
			$list->find();
			foreach ($list as $cal) {
				if ($cal->permitsPostingBy($_SESSION['USER'])) {
					$addable = true;
				}
			}
		}
		if ($addable) {
			$template->blocks[] = new Block('calendars/eventButtons.inc',
											array('calendar'=>$calendar));
		}
	}
}
else {
	$template->blocks[] = new Block('calendars/ical.inc',array('calendar'=>$calendar));
}
echo $template->render();

