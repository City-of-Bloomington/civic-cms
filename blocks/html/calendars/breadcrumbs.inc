<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
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
		<?php
			if (isset($this->event)) { $calendar = $this->event->getCalendar(); }
			else { $calendar = $this->calendar; }


			$url = new URL(BASE_URL.'/calendars');
			$name = View::escape($calendar->getName());
			if(!$name)
			{
				$name = 'All Calendars';
			}
			else
			{
				$url->calendar_id = $calendar->getId();
			}
			echo "<li><a href=\"$url\">$name</a></li>";
		?>
	</div>
	<h1><a href="<?php echo BASE_URL; ?>/calendars">City of Bloomington Calendars</a></h1>
</div>