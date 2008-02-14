<h1><a href="<?php echo BASE_URL; ?>/calendars">City of Bloomington Calendars</a></h1>
<?php
/**
 * @copyright Copyright (C) 2006,2007,2008 City of Bloomington, Indiana. All rights reserved.
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
		echo "<a class=\"editSmall\" href=\"".BASE_URL."/calendars/updateCalendar.php?calendar_id={$this->calendar->getId()}\">Edit</a>";
	}
	echo View::escape($this->calendar->getName()).'</h1>';
	echo "<p>".View::escape($this->calendar->getDescription())."</p>";
}
?>
<div class="contextualMenu">
	<form method="get" action="<?php echo BASE_URL; ?>/calendars">
	<fieldset>
		<?php
			$currentView = isset($_GET['view']) ? strtolower($_GET['view']) : 'list';
		?>
		<select name="view" onchange="this.form.submit();">
			<option value="day" <?php if($currentView=='day') echo 'selected="selected"'; ?>>Day View</option>
			<option value="week" <?php if($currentView=='week') echo 'selected="selected"'; ?>>Week View</option>
			<option value="list" <?php if($currentView=='list') echo 'selected="selected"'; ?>>List View</option>
			<option value="month" <?php if($currentView=='month') echo 'selected="selected"'; ?>>Month View</option>
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
				echo "<a class=\"add\" href=\"".BASE_URL."/calendars/addCalendar.php';\">Add Calendar</a>";
			}
		?>
	</fieldset>
	</form>
</div>
