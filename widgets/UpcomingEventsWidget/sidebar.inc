<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param array $recurrenceArray An array of EventRecurrences
 * $recurrenceArray will be a multi-dimensional array of EventRecurrences
 * in the form of $recurrenceArray[year][mon][mday] = EventRecurrence
 */
if (count($this->recurrenceArray))
{
	echo '
	<div class="widget">
		<h1>Upcoming Events</h1>
	';

	for($i=0; $i<$this->numDays; $i++)
	{
		$timestamp = strtotime("+$i day");

		$currentDateString = date('D, M j',$timestamp);

		$date = getdate($timestamp);
		$year = $date['year'];
		$month = $date['mon'];
		$day = $date['mday'];
		if (isset($this->recurrenceArray[$year][$month][$day]))
		{
			echo "<h4>$currentDateString</h4>";
			echo '<ul>';
			foreach($this->recurrenceArray[$year][$month][$day] as $r)
			{
				$title = View::escape($r->getEvent()->getTitle());
				echo "<li><a href=\"{$r->getEvent()->getURL()}\">$title</a></li>";
			}
			echo '</ul>';
		}
	}

	echo '</div>';
}
