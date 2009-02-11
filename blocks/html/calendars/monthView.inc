<?php
/**
 * @copyright Copyright (C) 2006-2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param object $this->calendar The calendar holding all the events we want to display
 * @param array $this->date A date so we know which year/month to display
 */
	$start = mktime(0,0,0,$this->date['mon'],1,$this->date['year']);
	$end = strtotime('+1 month',$start);

	$recurrences = $this->calendar->getEventRecurrenceArray($start,$end);

	$date = getdate($start);
	$year = $date['year'];
	$month = $date['mon'];
?>
<table class="calendar">
<tr><th colspan="2">
<?php
	$back = getdate(strtotime('-1 month',$start));
	$next = getdate($end);
	$url = new URL($_SERVER['SERVER_NAME'].$_SERVER['REQUEST_URI']);

	$url->year = $back['year'];
	$url->mon = $back['mon'];
		echo "
		<button type=\"button\" class=\"previous\" onclick=\"document.location.href='$url';\">
			Previous Month
		</button>
		";

	$monthName = date('F',$start);
	echo "{$this->calendar->getName()} $monthName $year";

	$url->year = $next['year'];
	$url->mon = $next['mon'];
		echo "
		<button type=\"button\" class=\"next\" onclick=\"document.location.href='$url';\">
			Next Month
		</button>
		";
?>
</th></tr>
<?php
	# Loop through all the days of the month
	$day = 1;
	$lastDayOfMonth = date('j',strtotime('-1 day',$end));
	while($day <= $lastDayOfMonth)
	{
		# Markup for a single day in the calendar
		$url = new URL(BASE_URL.'/calendars');
		$url->parameters = array('year'=>$year,'mon'=>$month,'mday'=>$day);
		if ($this->calendar->getId()) { $url->parameters['calendar_id'] = $this->calendar->getId(); }
		$url->parameters['view'] = 'day';

		$dayOfWeek = date('l',mktime(0,0,0,$month,$day,$year));
		$hasEvent = (isset($recurrences[$year][$month][$day]) && count($recurrences[$year][$month][$day])) ? ' hasEvent' : '';

		echo "
		<tr class=\"$dayOfWeek$hasEvent\">
			<th class=\"date\"><a href=\"{$url->getURL()}\">$day</a></th>
			<td>
		";
		if (isset($recurrences[$year][$month][$day]))
		{
			echo '<ul>';
			foreach($recurrences[$year][$month][$day] as $recurrence)
			{
				$time = $recurrence->getEvent()->isAllDayEvent() ? '' : $recurrence->getStart('g:i A');
				$title = View::escape($recurrence->getEvent()->getTitle());
				echo "
				<li><a href=\"".BASE_URL."/calendars/viewEvent.php?event_id={$recurrence->getEvent_id()};date=$year-$month-$day\">
					$time $title
					</a>
				</li>
				";
			}
			echo '</ul>';
		}
		echo "
			</td>
		</tr>
		";

		$day++;
	}
?>
</table>
