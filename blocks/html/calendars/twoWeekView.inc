<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Calendar $this->calendar
 * @param array $this->date
 * Display 14 days of events starting on the given date
 */
?>
<div class="interfaceBox">
	<h1>
		<?php
			$rangeStart = mktime(0,0,0,$this->date['mon'],$this->date['mday'],$this->date['year']);
			$rangeEnd = strtotime('+14 day',$rangeStart);

			$back = getdate(strtotime('-14 day',$rangeStart));
			$url = new URL("http://$_SERVER[SERVER_NAME]$_SERVER[REQUEST_URI]");
			$url->parameters['mon'] = $back['mon'];
			$url->parameters['mday'] = $back['mday'];
			$url->parameters['year'] = $back['year'];
			echo "<button type=\"button\" class=\"previous\" onclick=\"document.location.href='{$url->getURL()}';\">Previous Two Weeks</button>";


			echo date('M j,Y',$rangeStart).' to '.date('M j,Y',$rangeEnd);


			$next = getdate($rangeEnd);
			$url->parameters['mon'] = $next['mon'];
			$url->parameters['mday'] = $next['mday'];
			$url->parameters['year'] = $next['year'];
			echo "<button type=\"button\" class=\"next\" onclick=\"document.location.href='{$url->getURL()}';\">Next Two Weeks</button>";
		?>
	</h1>
	<table class="calendar">
	<?php
		for($i=0; $i<=14; $i++)
		{
			$timestamp = strtotime("+$i day",$rangeStart);

			$currentDateString = date('D, M j',$timestamp);
			echo "
			<tr><th>$currentDateString</th>
				<td>
			";

			$date = getdate($timestamp);
			$year = $date['year'];
			$month = $date['mon'];
			$day = $date['mday'];
			$recurrences = $this->calendar->getEventRecurrenceArray($rangeStart,$rangeEnd);
			if (isset($recurrences[$year][$month][$day]))
			{
				echo '<ul>';
				foreach($recurrences[$year][$month][$day] as $recurrence)
				{
					$time = $recurrence->getEvent()->isAllDayEvent() ? '' : $recurrence->getStart('g:i A');
					$title = View::escape($recurrence->getEvent()->getTitle());
					echo "
					<li><a href=\"".BASE_URL."/calendars/viewEvent.php?event_id={$recurrence->getEvent_id()}\">
						$time $title</a></li>
					";
				}
				echo '</ul>';
			}
			echo "</td></tr>";
		}
	?>
	</table>
</div>
