<?php
/**
 * @copyright Copyright (C) 2006-2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Calendar $this->calendar
 * @param array $this->date
 * Display 7 days of events starting on the given date
 */
?>
<div class="interfaceBox">
	<h2>
		<?php
			$rangeStart = mktime(0,0,0,$this->date['mon'],$this->date['mday'],$this->date['year']);
			$rangeEnd = strtotime('+7 day',$rangeStart);

			$back = getdate(strtotime('-7 day',$rangeStart));
			$url = new URL($_SERVER['SERVER_NAME'].$_SERVER['REQUEST_URI']);
			$url->parameters['mon'] = $back['mon'];
			$url->parameters['mday'] = $back['mday'];
			$url->parameters['year'] = $back['year'];
			echo "<a class=\"previous\" href=\"{$url->getURL()}\">Previous Week</a>";


			echo date('M j,Y',$rangeStart).' to '.date('M j,Y',$rangeEnd);


			$next = getdate($rangeEnd);
			$url->parameters['mon'] = $next['mon'];
			$url->parameters['mday'] = $next['mday'];
			$url->parameters['year'] = $next['year'];
			echo "<a class=\"next\" href=\"{$url->getURL()}\">Next Week</a>";
		?>
	</h2>
	<table class="calendar">
	<?php
		# We only want to iterate through one week
		for($i=0; $i<=7; $i++)
		{
			$timestamp = strtotime("+$i day",$rangeStart);

			$date = getdate($timestamp);
			$year = $date['year'];
			$month = $date['mon'];
			$day = $date['mday'];
			$recurrences = $this->calendar->getEventRecurrenceArray($rangeStart,$rangeEnd);

			$currentDateString = date('D, M j',$timestamp);
			$dayOfWeek = date('l',$timestamp);
			$hasEvent = (isset($recurrences[$year][$month][$day]) && count($recurrences[$year][$month][$day])) ? ' hasEvent' : '';
			echo "
			<tr class=\"$dayOfWeek$hasEvent\"><th>$currentDateString</th>
				<td>
			";

			if (isset($recurrences[$year][$month][$day]))
			{
				echo '<ul>';
				foreach($recurrences[$year][$month][$day] as $recurrence)
				{
					$time = $recurrence->getEvent()->isAllDayEvent() ? '' : $recurrence->getStart('g:i A');
					$title = View::escape($recurrence->getEvent()->getTitle());
					echo "
					<li><a href=\"".BASE_URL."/calendars/viewEvent.php?event_id={$recurrence->getEvent_id()};date=$year-$month-$day\">
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
