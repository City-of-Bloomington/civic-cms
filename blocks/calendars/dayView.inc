<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
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
		foreach($this->calendar->getEvents($this->date) as $event)
		{
			$time = $event->isAllDayEvent() ? '' : date('g:i A',strtotime($event->getStart()));
			echo "
			<tr><td>$time</td>
				<td><a href=\"".BASE_URL."/calendars/viewEvent.php?event_id={$event->getId()}\">
					{$event->getSummary()}</a>
				</td>
			</tr>
			";
		}
	?>
	</table>
</div>