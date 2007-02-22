<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Calendar $this->calendar
 * @param array $this->date
 */
	$timestamp = mktime(0,0,0,$this->date['mon'],$this->date['mday'],$this->date['year']);
	$date = getdate($timestamp);
	if ($date['weekday'] != 'Sunday') { $timestamp = strtotime('-1 Sunday',$timestamp); }
	$week = date('W',$timestamp);
?>
<div class="interfaceBox">
	<div class="titleBar"><?php echo "{$this->date['year']} Week $week"; ?></div>
	<table class="calendar">
	<?php
		$events = $this->calendar->getEventArray(array('week'=>$week));
		for($i=0; $i<=6; $i++)
		{
			$date = getdate(strtotime("+$i day",$timestamp));
			echo "
			<tr><th>$date[weekday], $date[year]-$date[mon]-$date[mday]</th>
				<td>
			";

			$year = $date['year'];
			$month = str_pad($date['mon'],2,'0',STR_PAD_LEFT);
			$day = str_pad($date['mday'],2,'0',STR_PAD_LEFT);
			if (isset($events[$year][$month][$day]))
			{
				echo '<ul>';
				foreach($events[$year][$month][$day] as $event)
				{
					$time = date('g:i A',strtotime($event->getStart()));
					echo "
					<li><a href=\"".BASE_URL."/calendars/viewEvent.php?event_id={$event->getId()}\">
						$time {$event->getSummary()}</a></li>
					";
				}
				echo '</ul>';
			}
			echo "</td></tr>";
		}
	?>
	</table>
</div>