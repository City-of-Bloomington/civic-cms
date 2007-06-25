<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Calendar $this->calendar
 * @param array $this->date
 */
?>
<div class="interfaceBox">
	<div class="titleBar">
		<?php
			$timestamp = mktime(0,0,0,$this->date['mon'],$this->date['mday'],$this->date['year']);
			$back = getdate(strtotime('-1 day',$timestamp));
			$next = getdate(strtotime('+1 day',$timestamp));

			$url = new URL($_SERVER['REQUEST_URI']);
			$url->parameters['mon'] = $back['mon'];
			$url->parameters['mday'] = $back['mday'];
			$url->parameters['year'] = $back['year'];
			echo "<button type=\"button\" class=\"back\" onclick=\"document.location.href='{$url->getURL()}';\">Back</button>";

			echo date('D, M j, Y',$timestamp);

			$url->parameters['mon'] = $next['mon'];
			$url->parameters['mday'] = $next['mday'];
			$url->parameters['year'] = $next['year'];
			echo "<button type=\"button\" class=\"next\" onclick=\"document.location.href='{$url->getURL()}';\">Next</button>";
		?>
	</div>
	<table>
	<?php
		$year = $this->date['year'];
		$month = str_pad($this->date['mon'],2,'0',STR_PAD_LEFT);
		$day = str_pad($this->date['mday'],2,'0',STR_PAD_LEFT);
		$recurrences = $this->calendar->getEventRecurrenceArray($timestamp);
		if (isset($recurrences[$year][$month][$day]))
		{
			foreach($recurrences[$year][$month][$day] as $recurrence)
			{
				$time = $recurrence->getEvent()->isAllDayEvent() ? '' : date('g:i A',strtotime($recurrence->getStart()));
				$summary = View::escape($recurrence->getEvent()->getSummary());
				echo "
				<tr><td>$time</td>
					<td><a href=\"".BASE_URL."/calendars/viewEvent.php?event_id={$recurrence->getEvent_id()}\">
						$summary</a>
					</td>
				</tr>
				";
			}
		}
	?>
	</table>
</div>
