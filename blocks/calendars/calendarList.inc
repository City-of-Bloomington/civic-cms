<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
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
				echo "
				<li><button type=\"button\" class=\"editSmall\" onclick=\"document.location.href='".BASE_URL."/calendars/updateCalendar.php?id={$calendar->getId()}';\">Edit</button>
					{$calendar->getName()}</li>
				";
			}
		?>
	</ul>
</div>