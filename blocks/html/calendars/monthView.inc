<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
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
<div class="interfaceBox">
	<div class="titleBar">
	<?php
		$back = getdate(strtotime('-1 month',$start));
		$next = getdate($end);
		$url = new URL("http://$_SERVER[SERVER_NAME]$_SERVER[REQUEST_URI]");

		$url->parameters['year'] = $back['year'];
		$url->parameters['mon'] = $back['mon'];
		echo "<button type=\"button\" class=\"previous\" onclick=\"document.location.href='{$url->getURL()}'\">Previous Month</button>";

		$monthName = date('F',$start);
		echo "{$this->calendar->getName()} $monthName $year";

		$url->parameters['year'] = $next['year'];
		$url->parameters['mon'] = $next['mon'];
		echo "<button type=\"button\" class=\"next\" onclick=\"document.location.href='{$url->getURL()}'\">Next Month</button>";
	?>
	</div>
<table class="calendar">
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

		echo "
		<tr><th class=\"date\"><a href=\"{$url->getURL()}\">$day</a></th>
			<td>
		";
		if (isset($recurrences[$year][$month][$day]))
		{
			if (count($recurrences[$year][$month][$day]))
			{
				echo '<ul>';
				foreach($recurrences[$year][$month][$day] as $recurrence)
				{
					$time = $recurrence->getEvent()->isAllDayEvent() ? '' : $recurrence->getStart('g:i A');
					$title = View::escape($recurrence->getEvent()->getTitle());
					echo "
					<li><a href=\"".BASE_URL."/calendars/viewEvent.php?event_id={$recurrence->getEvent_id()}\">
						$time $title
						</a>
					</li>
					";
				}
				echo '</ul>';
			}
			else { echo 'none'; }
		}
		else { echo 'none'; }
		echo "
			</td>
		</tr>
		";

		$day++;
	}
?>
</table>
