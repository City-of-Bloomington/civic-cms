<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Event $this->event
 */
?>
<h1>Update Event</h1>
<form method="post" action="<?php echo $_SERVER['PHP_SELF']; ?>">
<fieldset><legend>Event Info</legend>
	<input name="event_id" type="hidden" value="<?php echo $this->event->getId(); ?>" />
	<table>

	<tr><td><label for="event-summary">Title</label></td>
		<td><input name="event[summary]" id="event-summary" size="60" value="<?php echo View::escape($this->event->getSummary()); ?>" /></td></tr>

	<tr><td><label for="event-location_id">Location</label></td>
		<td><select name="event[location_id]" id="event-location_id">
			<?php
				$list = new LocationList();
				$list->find();
				foreach($list as $location)
				{
					$name = View::escape($location->getName());
					$selected = ($this->event->getLocation_id()==$location->getId()) ? 'selected="selected"' : '';
					echo "<option value=\"{$location->getId()}\" $selected>$name</option>";
				}
			?>
			</select>
		</td>
	</tr>

	<tr><td><label for="event-calendar_id">Calendar</label></td>
		<td><select name="event[calendar_id]" id="event-calendar_id">
			<?php
				$list = new CalendarList();
				$list->find();
				foreach($list as $calendar)
				{
					$name = View::escape($calendar->getName());
					$selected = ($this->event->getCalendar_id() == $calendar->getId());
					echo "<option value=\"{$calendar->getId()}\" $selected>$name</option>";
				}
			?>
			</select>
		</td>
	</tr>

	<?php $start = strtotime($this->event->getStart()); ?>
	<tr><td><label for="startDate">Start time</label></td>
		<td><input name="startDate" id="startDate" size="10" maxlength="10" value="<?php echo date('n/j/Y',$start); ?>" />
			<input name="startTime" id="startTime" size="7" maxlength="7" value="<?php echo date('g:ia',$start); ?>" />
			<?php $checked = $this->event->isAllDayEvent() ? 'checked="checked"' : ''; ?>
			<input name="allDayEvent" id="allDayEvent" type="checkbox" value="1" <?php echo $checked; ?> onclick="toggleTimes();" />
			<label for="allDayEvent">All Day Event</label>
		</td>
	</tr>
	<?php $end = strtotime($this->event->getEnd()); ?>
	<tr><td><label for="endDate">End time</label></td>
		<td><input name="endDate" id="endDate" size="10" maxlength="10" value="<?php echo date('n/j/Y',$end); ?>" />
			<input name="endTime" id="endTime" size="7" maxlength="7" value="<?php echo date('g:ia',$end); ?>" />
		</td>
	</tr>

	<tr><td colspan="2">
			<div><label for="event-description">Description</label></div>
			<textarea name="event[description]" id="event-description" rows="3" cols="60"><?php echo View::escape($this->event->getDescription()); ?></textarea>
	</td></tr>

	</table>
</fieldset>

<fieldset><legend>Sections</legend>
	<p>Where on the site do you want this event to show up?</p>
	<table>
	<?php
		$sections = new SectionList();
		if (userHasRole(array('Administrator','Webmaster'))) { $sections->find(); }
		else { $sections->find(array('department_id'=>$_SESSION['USER']->getDepartment_id())); }

		foreach($sections as $section)
		{
			$name = View::escape($section->getName());
			$checked = $this->event->hasSection($section) ? 'checked="checked"' : '';
			echo "
			<tr><td><input name=\"event[sections][{$section->getId()}]\" id=\"event-sections-{$section->getId()}\" type=\"checkbox\" value=\"{$section->getId()}\" $checked /></td>
				<td><label for=\"event-sections-{$section->getId()}\">$name</label></td></tr>
			";
		}
	?>
	</table>
</fieldset>

<fieldset><legend>Submit</legend>
	<button type="submit" class="submit">Submit</button>
	<a class="cancel" href="<?php echo BASE_URL; ?>/calendars">Cancel</a>
</fieldset>
</form>

<script type="text/javascript">
	var startValue = document.getElementById("startTime").value;
	var endValue = document.getElementById("endTime").value;

	function toggleTimes()
	{
		var startTime = document.getElementById("startTime");
		var endTime = document.getElementById("endTime");

		if (startTime.style.display == "none")
		{
			startTime.value = startValue;
			endTime.value = endValue;
			startTime.style.display = "";
			endTime.style.display = "";
		}
		else
		{
			startTime.value = "";
			endTime.value = "";
			startTime.style.display = "none";
			endTime.style.display = "none";
		}
	}
	<?php
		if ($this->event->isAllDayEvent())
		{
			echo '
			document.getElementById("startTime").value = "";
			document.getElementById("endTime").value = "";
			document.getElementById("startTime").style.display = "none";
			document.getElementById("endTime").style.display = "none";
			';
		}
	?>
</script>
