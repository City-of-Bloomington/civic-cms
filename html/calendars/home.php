<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET calendar_id
 */
	$calendar = isset($_GET['calendar_id']) ? new Calendar($_GET['calendar_id']) : new Calendar();
	$template = isset($_GET['format']) ? new Template($_GET['format'],$_GET['format']) : new Template();

	if ($template->outputFormat==='html')
	{
		# Figure out which display we're going to use
		if (isset($_GET['view']))
		{
			switch ($_GET['view'])
			{
				case 'month': $block = 'calendars/monthView.inc'; break;
				case 'twoweek': $block = 'calendars/twoWeekView.inc'; break;
				case 'week': $block = 'calendars/weekView.inc'; break;
				case 'day': $block = 'calendars/dayView.inc'; break;
				default: $block = 'calendars/weekView.inc';
			}
		}
		else { $block = 'calendars/weekView.inc'; }

		# Get the date that we're wanting to display
		$now = getdate();
		if (isset($_GET['year']) || isset($_GET['mon']) || isset($_GET['mday']))
		{
			$date['year'] = isset($_GET['year']) ? $_GET['year'] : $now['year'];
			$date['mon'] = isset($_GET['mon']) ? $_GET['mon'] : $now['mon'];
			$date['mday'] = isset($_GET['mday']) ? $_GET['mday'] : $now['mday'];
		}
		else { $date = $now; }

		$url = new URL("http://$_SERVER[SERVER_NAME]$_SERVER[REQUEST_URI]");
		$template->blocks[] = new Block('calendars/breadcrumbs.inc',array('calendar'=>$calendar));
		$template->blocks[] = new Block('calendars/viewButtons.inc',array('url'=>$url,'calendar'=>$calendar));
		$template->blocks[] = new Block($block,array('calendar'=>$calendar,'date'=>$date));


		# Only show the event buttons if they can actually add an event
		$addable = false;
		if (isset($_SESSION['USER']))
		{
			$list = new CalendarList();
			$list->find();
			foreach($list as $cal)
			{
				if ($cal->permitsPostingBy($_SESSION['USER'])) { $addable = true; }
			}
		}

		if ($addable) { $template->blocks[] = new Block('calendars/eventButtons.inc',array('calendar'=>$calendar)); }
	}
	if ($template->outputFormat==='ical')
	{
		$template->blocks[] = new Block('calendars/ical.inc',array('calendar'=>$calendar));
	}
	$template->render();
?>
