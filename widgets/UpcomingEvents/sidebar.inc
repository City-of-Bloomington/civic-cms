<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param array $upcomingEvents
 */
	if (count($upcomingEvents))
	{
		echo '
		<div class="widget">
			<div class="titleBar">Upcoming Events</div>
			<ul>
		';
		foreach($upcomingEvents as $event)
		{
			$start = date('Y-m-d g:i A',strtotime($event->getStart()));
			echo "
			<li><a href=\"".BASE_URL."/calendars/viewEvent.php?event_id={$event->getId()}\">
				{$event->getSummary()} $start
			</li>
			";
		}
		echo '</ul></div>';
	}
?>