<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
?>
<div class="interfaceBox">
	<div class="titleBar">
		<button type="button" class="addSmall" onclick="document.location.href='<?php echo BASE_URL; ?>/calendars/addCalendar.php';">Add</button>
		Calendars
	</div>
	<ul><?php
			foreach($this->calendarList as $calendar)
			{
				$name = View::escape($calendar->getName());
				echo "
				<li><button type=\"button\" class=\"editSmall\" onclick=\"document.location.href='".BASE_URL."/calendars/updateCalendar.php?id={$calendar->getId()}';\">Edit</button>
					<a href=\"".BASE_URL."/calendars/viewCalendar.php?calendar_id={$calendar->getId()}\">$name</a></li>
				";
			}
		?>
	</ul>
</div>
