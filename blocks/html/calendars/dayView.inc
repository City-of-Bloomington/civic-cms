<?php
/**
 * @copyright Copyright (C) 2006-2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Calendar $this->calendar
 * @param array $this->date
 */
?>
<table class="calendar">
<tr><th colspan="2">
	<?php
		$rangeStart = mktime(0,0,0,$this->date['mon'],$this->date['mday'],$this->date['year']);
		$rangeEnd = strtotime('+1 day',$rangeStart);

		$back = getdate(strtotime('-1 day',$rangeStart));
		$next = getdate($rangeEnd);

		$url = new URL($_SERVER['SERVER_NAME'].$_SERVER['REQUEST_URI']);
		$url->mon = $back['mon'];
		$url->mday = $back['mday'];
		$url->year = $back['year'];
		echo "
		<button type=\"button\" class=\"previous\" onclick=\"document.location.href='$url';\">
			Previous Day
		</button>
		";

		echo date('D, M j, Y',$rangeStart);

		$url->mon = $next['mon'];
		$url->mday = $next['mday'];
		$url->year = $next['year'];
		echo "
		<button type=\"button\" class=\"next\" onclick=\"document.location.href='$url';\">
			Next Day
		</button>
		";
	?>
</th></tr>
<?php
	$year = $this->date['year'];
	$month = $this->date['mon'];
	$day = $this->date['mday'];
	$recurrences = $this->calendar->getEventRecurrenceArray($rangeStart,$rangeEnd);
	if (isset($recurrences[$year][$month][$day]))
	{
		if (count($recurrences[$year][$month][$day]))
		{
			foreach($recurrences[$year][$month][$day] as $recurrence)
			{
				$time = $recurrence->getEvent()->isAllDayEvent() ? '' : $recurrence->getStart('g:i A');
				$title = View::escape($recurrence->getEvent()->getTitle());
				echo "
				<tr><td>$time</td>
					<td><a href=\"".BASE_URL."/calendars/viewEvent.php?event_id={$recurrence->getEvent_id()};date=$year-$month-$day\">
						$title</a>
					</td>
				</tr>
				";
			}
		}
		else { echo '<tr><td colspan="2">No events scheduled in this calendar</td></tr>'; }
	}
	else { echo '<tr><td colspan="2">No events scheduled in this calendar</td></tr>'; }
?>
</table>
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
