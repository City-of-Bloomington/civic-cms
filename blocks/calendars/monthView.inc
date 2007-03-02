<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param object $this->calendar The calendar holding all the events we want to display
 * @param array $this->date A date so we know which year/month to display
 */
	$timestamp = mktime(0,0,0,$this->date['mon'],1,$this->date['year']);
	$calendarDate = getdate($timestamp);
	$year = $calendarDate['year'];
	$month = str_pad($calendarDate['mon'],2,'0',STR_PAD_LEFT);
	$lastDayOfMonth = date('t',$timestamp);
	$events = $this->calendar->getEventArray();
?>
<table class="calendar">
<tr><th colspan="7">
	<?php
		$back = getdate(strtotime('-1 month',$timestamp));
		$next = getdate(strtotime('+1 month',$timestamp));
		$url = new URL($_SERVER['REQUEST_URI']);

		$url->parameters['year'] = $back['year'];
		$url->parameters['mon'] = $back['mon'];
		echo "<button type=\"button\" class=\"back\" onclick=\"document.location.href='{$url->getURL()}'\">Back</button>";

		echo "{$this->calendar->getName()} $calendarDate[month] $year";

		$url->parameters['year'] = $next['year'];
		$url->parameters['mon'] = $next['mon'];
		echo "<button type=\"button\" class=\"next\" onclick=\"document.location.href='{$url->getURL()}'\">Next</button>";
	?>
	</th>
</tr>
<tr><th>S</th><th>M</th><th>T</th><th>W</th><th>R</th><th>F</th><th>S</th></tr>
<?php

	$firstWeekDay = $calendarDate['wday'];
	$currentWeekDay = $firstWeekDay;
	$firstweek = true;
	$currentDay = 1;


	# Loop through all the days of the month
	while($currentDay <= $lastDayOfMonth)
	{
		# Draw blank days for the first week
		if ($firstweek)
		{
			echo "<tr>";
			for($i=1; $i<=$firstWeekDay; $i++) { echo "<td></td>"; }
			$firstweek = false;
		}

		# Start a new row each sunday
		if ($currentWeekDay == 0) { echo "<tr>"; }

		# Markup for a single day in the calendar
		$url = new URL(BASE_URL.'/calendars');
		$url->parameters = array('year'=>$year,'mon'=>$month,'mday'=>$currentDay);
		if ($this->calendar->getId()) { $url->parameters['calendar_id'] = $this->calendar->getId(); }
		$url->parameters['view'] = 'day';

		echo "<td><span class=\"date\"><a href=\"{$url->getURL()}\">$currentDay</a></span>";
		$day = str_pad($currentDay,2,'0',STR_PAD_LEFT);
		if (isset($events[$year][$month][$day]))
		{
			echo '<ul>';
			foreach($events[$year][$month][$day] as $event)
			{
				$time = $event->isAllDayEvent() ? '' : date('g:i A',strtotime($event->getStart()));
				echo "
				<li><a href=\"".BASE_URL."/calendars/viewEvent.php?event_id={$event->getId()}\">
					$time {$event->getSummary()}</a></li>
				";
			}
			echo '</ul>';
		}
		echo "</td>\n";


		# Close off each row on Saturday
		if ($currentWeekDay == 6) { echo "</tr>"; }



		$currentWeekDay++;
		$currentWeekDay = $currentWeekDay % 7;
		$currentDay++;
	}

	# Finish out the table with blank days
	for($i=$currentWeekDay; $i % 7 != 0; $i++) { echo "<td></td>"; }

?>
</tr>
</table>