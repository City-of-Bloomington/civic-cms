<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param array $upcomingEvents An array of EventRecurrences
 */
if (count($this->upcomingEvents))
{
	echo '
	<div class="widget">
		<h1>Upcoming Events</h1>
		<ul>
	';
	foreach($this->upcomingEvents as $recurrence)
	{
		$title = View::escape($recurrence->getEvent()->getTitle());
		$start = date('Y-m-d H:i:s',$recurrence->getStart());
		echo "
		<li><a href=\"".BASE_URL."/calendars/viewEvent.php?event_id={$recurrence->getEvent_id()}\">
			$title $start</a>
		</li>
		";
	}
	echo '</ul></div>';
}
