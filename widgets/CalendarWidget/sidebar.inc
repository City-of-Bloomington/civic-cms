<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
	$calendar = new Calendar();
	$date = getdate();

	$rangeStart = mktime(0,0,0,$date['mon'],1,$date['year']);
	$rangeEnd = strtotime('+1 month',$rangeStart);
	$recurrences = $calendar->getEventRecurrenceArray($rangeStart,$rangeEnd);

	$calendarDate = getdate($rangeStart);
	$year = $calendarDate['year'];
	$month = $calendarDate['mon'];
	$lastDayOfMonth = date('t',$rangeStart);
?>
<div class="widget">
<h1>Calendar
	<?php
		$feedsURL = new URL(BASE_URL.'/feeds');
		$feedsURL->type = 'webcal';
		$feedsURL->url = BASE_URL.'/calendars?format=ical';
	?>
	<button type="button" class="ical" onclick="document.location.href='<?php echo $feedsURL; ?>';">Subscribe</button>
</h1>
<table class="calendar">
<tr><th colspan="7"><?php echo $calendarDate['month']; ?></th></tr>
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
		if ($calendar->getId()) { $url->parameters['calendar_id'] = $calendar->getId(); }
		$url->parameters['view'] = 'day';

		$day = $currentDay;
		$dayOfWeek = date('l',mktime(0,0,0,$month,$day,$year));
		if (isset($recurrences[$year][$month][$day]))
		{
			echo "<td class=\"$dayOfWeek hasEvent\"><a href=\"{$url->getURL()}\">$currentDay</a>";
		}
		else { echo "<td class=\"$dayOfWeek\">$currentDay"; }
		echo "</td>";


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
</div>
<?php
	/* Debug Code
	echo '<ul>';
	foreach($recurrences as $y=>$months)
	{
		echo "<li>$y<ul>";
		foreach($months as $m=>$days)
		{
			echo "<li>$m<ul>";
			foreach($days as $d=>$recs)
			{
				echo "<li>$d<ul>";
				foreach($recs as $r)
				{
					echo "<li>".$r->getEvent_id().$r->getStart('Y-m-d H:i:s')."</li>";
				}
				echo "</ul></li>";
			}
			echo "</ul></li>";
		}
		echo "</ul></li>";
	}
	echo '</ul>';
	*/
?>
