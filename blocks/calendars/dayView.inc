<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
/*
	$this->calendar
	$this->date
*/
?>
<div class="interfaceBox">
	<div class="titleBar"><?php echo "{$this->date['mon']}-{$this->date['mday']}-{$this->date['year']}"; ?></div>
	<table>
	<?php
		foreach($this->calendar->getEvents($this->date) as $event)
		{
			$time = date('g:i A',strtotime($event->getStart()));
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