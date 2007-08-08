<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param array $upcomingEvents
 */
	if (count($this->upcomingEvents))
	{
		echo '
		<div class="widget">
			<div class="titleBar">Upcoming Events</div>
			<ul>
		';
		foreach($this->upcomingEvents as $event)
		{
			echo "
			<li><a href=\"".BASE_URL."/calendars/viewEvent.php?event_id={$event->getId()}\">
				{$event->getSummary()} {$event->getStartDate()}</a>
			</li>
			";
		}
		echo '</ul></div>';
	}
?>