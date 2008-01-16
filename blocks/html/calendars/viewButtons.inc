<h1><a href="<?php echo BASE_URL; ?>/calendars">City of Bloomington Calendars</a></h1>
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
		echo '<h1>';
		if (isset($_SESSION['USER']) && $this->calendar->permitsEditingBy($_SESSION['USER']))
		{
			echo "<button type=\"button\" class=\"editSmall\" onclick=\"document.location.href='".BASE_URL."/calendars/updateCalendar.php?calendar_id={$this->calendar->getId()}';\">Edit</button>";
		}
		echo View::escape($this->calendar->getName()).'</h1>';
		echo "<p>".View::escape($this->calendar->getDescription())."</p>";
	}
?>
<div class="contextualMenu">
	<form method="get" action="<?php echo BASE_URL; ?>/calendars">
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

			$this->url->parameters['view'] = 'twoweek';
			$twoweek = $this->url->getURL();

			$this->url->parameters['view'] = 'month';
			$month = $this->url->getURL();

			$currentView = isset($_GET['view']) ? strtolower($_GET['view']) : 'week';
		?>
		<select name="view" onchange="document.location.href=this.options[this.options.selectedIndex].value;">
			<option value="<?php echo $day; ?>" <?php if($currentView=='day') echo 'selected="selected"'; ?>>Day View</option>
			<option value="<?php echo $week; ?>" <?php if($currentView=='week') echo 'selected="selected"'; ?>>Week View</option>
			<option value="<?php echo $twoweek; ?>" <?php if($currentView=='twoweek') echo 'selected="selected"'; ?>>Two-Week View</option>
			<option value="<?php echo $month; ?>" <?php if($currentView=='month') echo 'selected="selected"'; ?>>Month View</option>
		</select>

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
