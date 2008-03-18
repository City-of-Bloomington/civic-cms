<?php
/**
 * @copyright Copyright (C) 2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Calendar $this->calendar
 * @param array $this->date
 */
$MAX_DAYS_AHEAD = 60;
$MAX_EVENTS = 15;
?>
<div class="interfaceBox">
	<h2>Upcoming Events</h2>
	<table class="calendar">
	<?php
		$rangeStart = time();
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
</div>
