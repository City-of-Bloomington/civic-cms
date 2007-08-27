<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Calendar $this->calendar
 * @param array $this->date
 * Display 14 days of events starting on the given date
 */
	$now = mktime(0,0,0,$this->date['mon'],$this->date['mday'],$this->date['year']);
	$then = strtotime('+14 day',$now);

	$recurrences = $this->calendar->getEventRecurrenceArray($now,$then);
?>
<div class="interfaceBox">
	<div class="titleBar"><?php echo date('M j,Y',$now).' to '.date('M j,Y',$then); ?></div>
	<table class="calendar">
	<?php
		for($i=0; $i<=13; $i++)
		{
			$timestamp = strtotime("+$i day",$now);
			$date = getdate($timestamp);

			$currentDateString = date('D, M j',$timestamp);
			echo "
			<tr><th>$currentDateString</th>
				<td>
			";

			$year = $date['year'];
			$month = str_pad($date['mon'],2,'0',STR_PAD_LEFT);
			$day = str_pad($date['mday'],2,'0',STR_PAD_LEFT);
			if (isset($recurrences[$year][$month][$day]))
			{
				echo '<ul>';
				foreach($recurrences[$year][$month][$day] as $recurrence)
				{
					$time = $recurrence->getEvent()->isAllDayEvent() ? '' : date('g:i A',strtotime($recurrence->getStart()));
					$summary = View::escape($recurrence->getEvent()->getSummary());
					echo "
					<li><a href=\"".BASE_URL."/calendars/viewEvent.php?event_id={$recurrence->getEvent_id()}\">
						$time $summary</a></li>
					";
				}
				echo '</ul>';
			}
			echo "</td></tr>";
		}
	?>
	</table>
</div>
