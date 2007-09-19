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
	$recurrences = $this->calendar->getEventRecurrenceArray();
?>
<div class="interfaceBox">
	<div class="titleBar">
	<?php
		$back = getdate(strtotime('-1 month',$timestamp));
		$next = getdate(strtotime('+1 month',$timestamp));
		$url = new URL($_SERVER['REQUEST_URI']);

		$url->parameters['year'] = $back['year'];
		$url->parameters['mon'] = $back['mon'];
		echo "<button type=\"button\" class=\"back\" onclick=\"document.location.href='{$url->getURL()}'\">Previous Month</button>";

		echo "{$this->calendar->getName()} $calendarDate[month] $year";

		$url->parameters['year'] = $next['year'];
		$url->parameters['mon'] = $next['mon'];
		echo "<button type=\"button\" class=\"next\" onclick=\"document.location.href='{$url->getURL()}'\">Next Month</button>";
	?>
	</div>
<table class="calendar">
<?php
	# Loop through all the days of the month
	$currentDay = 1;
	while($currentDay <= $lastDayOfMonth)
	{
		# Markup for a single day in the calendar
		$url = new URL(BASE_URL.'/calendars');
		$url->parameters = array('year'=>$year,'mon'=>$month,'mday'=>$currentDay);
		if ($this->calendar->getId()) { $url->parameters['calendar_id'] = $this->calendar->getId(); }
		$url->parameters['view'] = 'day';

		echo "
		<tr><th class=\"date\"><a href=\"{$url->getURL()}\">$currentDay</a></th>
			<td>
		";

		$day = str_pad($currentDay,2,'0',STR_PAD_LEFT);
		if (isset($recurrences[$year][$month][$day]))
		{
			echo '<ul>';
			foreach($recurrences[$year][$month][$day] as $recurrence)
			{
				$time = $recurrence->getEvent()->isAllDayEvent() ? '' : date('g:i A',strtotime($recurrence->getStart()));
				$summary = View::escape($recurrence->getEvent()->getSummary());
				echo "
				<li><a href=\"".BASE_URL."/calendars/viewEvent.php?event_id={$recurrence->getEvent_id()}\">
					$time
					$summary
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

		$currentDay++;
	}
?>
</table>
