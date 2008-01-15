<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
?>
<div class="interfaceBox">
	<div class="titleBar">
		<?php
			if (isset($_SESSION['USER']) && $calendar->permitsEditingBy($_SESSION['USER']))
			{
				echo "<button type=\"button\" class=\"addSmall\" onclick=\"document.location.href='".BASE_URL."/calendars/addCalendar.php';\">Add</button>";
			}
		?>
		<a href="<?php echo BASE_URL; ?>/calendars">Calendars</a>
	</div>
	<ul><?php
			$list = new CalendarList();
			$list->find();
			foreach($list as $calendar)
			{
				$name = View::escape($calendar->getName());

				if (isset($_SESSION['USER']) && $calendar->permitsEditingBy($_SESSION['USER']))
				{
					$editButton = "<button type=\"button\" class=\"editSmall\" onclick=\"document.location.href='".BASE_URL."/calendars/updateCalendar.php?id={$calendar->getId()}';\">Edit</button>";
				}
				else { $editButton = ''; }

				echo "
				<li>$editButton
					<a href=\"".BASE_URL."/calendars/viewCalendar.php?calendar_id={$calendar->getId()}\">$name</a>
				</li>
				";
			}
		?>
	</ul>
</div>
