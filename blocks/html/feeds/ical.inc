<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
?>
<h2 id="calendar_feeds">Calendar Feeds</h2>
<p>If you keep track of events on multiple websites that use calendar feeds,
you can view them together using a web-calendar application, such as iCal for
Mac users or <a href="http://www.mozilla.org/projects/calendar/">Mozilla's Calendar Project</a>
for PC users.  Follow the intructions of your application to add one of our calendar feeds.
</p>
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
