<?php
/**
 * @copyright Copyright (C) 2007-2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Calendar $this->calendar
 * @param Event $this->event
 * Either an event or a calendar must be passed
 */
?>
<div id="pageTitle">
	<div class="breadcrumbs">
	<ul><li><a href="<?php echo BASE_URL; ?>">Home</a></li>
		<li><a href="<?php echo BASE_URL; ?>/calendars">Calendars</a></li>
	</ul>
	</div>
	<h1><?php
			if (isset($this->event)) { $calendar = $this->event->getCalendar(); }
			else { $calendar = $this->calendar; }

			if (isset($_SESSION['USER']) && $this->calendar->permitsEditingBy($_SESSION['USER']))
			{
				echo "<a class=\"editSmall\" href=\"".BASE_URL."/calendars/updateCalendar.php?calendar_id={$this->calendar->getId()}\">Edit</a>";
			}
			echo $calendar->getName() ? View::escape($calendar->getName()) : 'All Calendars';
		?>
	</h1>
</div>
