<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
?>
<h1>Calendar Feeds</h1>
<p>You can subscribe to any of our calendars using your own calendar program.
The calendars are available at these URLs.</p>
<table>
<tr><th>All Calendars</th>
	<td>
	<?php
		$url = new URL(BASE_URL.'/calendars?format=ical');
		$url->setProtocol('webcal://');
		echo "<a href=\"$url\">$url</a>";
	?>
	</td>
</tr>

<?php
	$list = new CalendarList();
	$list->find();
	foreach($list as $calendar)
	{
		$name = View::escape($calendar->getName());
		$url = new URL(BASE_URL.'/calendars?format=ical;calendar_id='.$calendar->getId());
		$url->setProtocol('webcal://');
		echo "<tr><th>$name</th><td><a href=\"$url\">$url</a></td></tr>";
	}
?>
</table>
