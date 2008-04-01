<?php
/**
 * @copyright Copyright (C) 2006-2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
?>
<div class="interfaceBox">
	<h2>
		<?php
			if (userHasRole(array('Administrator','Webmaster')))
			{
				echo "<a class=\"addSmall button\" href=\"".BASE_URL."/calendars/addCalendar.php\">Add</a>";
			}
		?>
		<a href="<?php echo BASE_URL; ?>/calendars">Calendars</a>
	</h2>
	<ul><?php
			$list = new CalendarList();
			$list->find();
			foreach($list as $calendar)
			{
				$name = View::escape($calendar->getName());

				if (isset($_SESSION['USER']) && $calendar->permitsEditingBy($_SESSION['USER']))
				{
					$editButton = "<a class=\"editSmall button\" href=\"".BASE_URL."/calendars/updateCalendar.php?id={$calendar->getId()}\">Edit</a>";
				}
				else { $editButton = ''; }

				echo "
				<li>$editButton
					<a href=\"{$calendar->getURL()}\">$name</a>
				</li>
				";
			}
		?>
	</ul>
</div>
