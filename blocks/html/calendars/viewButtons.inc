<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 *
 * @param URL $this->url
 * @param Calendar $this->calendar
 */
	if ($this->calendar->getName())
	{
		echo '<h2>';
		if (isset($_SESSION['USER']) && $this->calendar->permitsEditingBy($_SESSION['USER']))
		{
			echo "<button type=\"button\" class=\"editSmall\" onclick=\"document.location.href='".BASE_URL."/calendars/updateCalendar.php?calendar_id={$this->calendar->getId()}';\">Edit</button>";
		}
		echo View::escape($this->calendar->getName()).'</h2>';
		echo "<p>".View::escape($this->calendar->getDescription())."</p>";
	}
?>
<div class="contextualMenu">
	<form method="get" action="<?php $_SERVER['PHP_SELF']; ?>">
	<fieldset>
		<?php
			foreach($this->url->parameters as $field=>$value)
			{
				if ($field != 'calendar_id') { echo "<input name=\"$field\" type=\"hidden\" value=\"$value\" />"; }
			}
			$this->url->parameters['view'] = 'day';
			$day = $this->url->getURL();

			$this->url->parameters['view'] = 'week';
			$week = $this->url->getURL();

			$this->url->parameters['view'] = 'month';
			$month = $this->url->getURL();
		?>
		<button type="button" class="day" onclick="document.location.href='<?php echo $day; ?>';">Day View</button>
		<button type="button" class="week" onclick="document.location.href='<?php echo $week; ?>';">Week View</button>
		<button type="button" class="month" onclick="document.location.href='<?php echo $month; ?>';">Month View</button>

		<select name="calendar_id" onchange="this.form.submit();">
			<option value=''>All Calendars</option>
			<?php
				$list = new CalendarList();
				$list->find();
				foreach($list as $calendar)
				{
					$name = View::escape($calendar->getName());
					if ($this->calendar->getId() != $calendar->getId()) { echo "<option value=\"{$calendar->getId()}\">$name</option>"; }
					else { echo "<option value=\"{$calendar->getId()}\" selected=\"selected\">$name</option>"; }
				}
			?>
		</select>

		<?php
			if (userHasRole(array('Administrator','Webmaster')))
			{
				echo "<button type=\"button\" class=\"add\" onclick=\"document.location.href='".BASE_URL."/calendars/addCalendar.php';\">Add Calendar</button>";
			}
		?>
	</fieldset>
	</form>
</div>
