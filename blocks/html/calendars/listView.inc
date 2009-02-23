<?php
/**
 * @copyright Copyright (C) 2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Calendar $this->calendar
 * @param array $this->date
 *
 * List  a good number of events, based on MAX_DAYS_AHEAD and MAX_EVENTS
 * This screen navigates two weeks forward and back
 */
$MAX_DAYS_AHEAD = 60;
$MAX_EVENTS = 30;
?>
<h2>Upcoming Events</h2>
<table class="calendar">
<tr><th colspan="2">
	<?php
		$rangeStart = !isset($this->date) ? time() : mktime(0,0,0,$this->date['mon'],$this->date['mday'],$this->date['year']);
		$rangeEnd = strtotime('+7 day',$rangeStart);

		$back = getdate(strtotime('-7 day',$rangeStart));
		$url = new URL($_SERVER['SERVER_NAME'].$_SERVER['REQUEST_URI']);
		$url->parameters['mon'] = $back['mon'];
		$url->parameters['mday'] = $back['mday'];
		$url->parameters['year'] = $back['year'];
		echo "
		<button type=\"button\" class=\"previous\" onclick=\"document.location.href='$url';\">
			Previous
		</button>
		";


		echo 'Events starting '.date('M j,Y',$rangeStart).'...';


		$next = getdate($rangeEnd);
		$url->parameters['mon'] = $next['mon'];
		$url->parameters['mday'] = $next['mday'];
		$url->parameters['year'] = $next['year'];
		echo "
		<button type=\"button\" class=\"next\" onclick=\"document.location.href='$url';\">
			Next
		</button>
		";
	?>
</th></tr>
<?php
	$recurrences = $this->calendar->getEventRecurrenceArray($rangeStart);

	$numDaysAhead = 0;
	$numEventsDisplayed = 0;

	while($numDaysAhead<=$MAX_DAYS_AHEAD && $numEventsDisplayed<=$MAX_EVENTS)
	{
		$timestamp = strtotime("+$numDaysAhead day",$rangeStart);
		$date = getdate($timestamp);

		$year = $date['year'];
		$month = $date['mon'];
		$day = $date['mday'];

		$currentDateString = date('D, M j',$timestamp);
		$dayOfWeek = date('l',$timestamp);

		if (isset($recurrences[$year][$month][$day]))
		{
			echo "
			<tr class=\"$dayOfWeek hasEvent\"><th>$currentDateString</th>
				<td><ul>
			";
			foreach($recurrences[$year][$month][$day] as $recurrence)
			{
				$time = $recurrence->getEvent()->isAllDayEvent() ? '' : $recurrence->getStart('g:i A');
				$title = View::escape($recurrence->getEvent()->getTitle());
				echo "
				<li><a href=\"".BASE_URL."/calendars/viewEvent.php?event_id={$recurrence->getEvent_id()};date=$year-$month-$day\">
					$time $title</a></li>
				";
				$numEventsDisplayed++;
			}
			echo "
					</ul>
				</td>
			</tr>
			";
		}
		$numDaysAhead++;
	}
?>
</table>
