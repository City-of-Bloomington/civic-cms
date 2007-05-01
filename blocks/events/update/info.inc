<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Event $this->event
 */
?>
<form id="eventForm" method="post" action="<?php echo $_SERVER['PHP_SELF']; ?>">
<fieldset><legend>Event Info</legend>
	<table>
	<tr><td><label for="event-summary">Title</label></td>
		<td><input name="event[summary]" id="event-summary" value="<?php echo $this->event->getSummary(); ?>" /></td></tr>

	<tr><td><label for="event-location_id">Location</label></td>
		<td><select name="event[location_id]" id="event-location_id">
			<?php
				$list = new LocationList();
				$list->find();
				foreach($list as $location)
				{
					if ($this->event->getLocation_id()==$location->getId()) { echo "<option value=\"{$location->getId()}\" selected=\"selected\">$location</option>"; }
					else { echo "<option value=\"{$location->getId()}\">$location</option>"; }
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
					if ($this->event->getCalendar_id() == $calendar->getId()) { echo "<option value=\"{$calendar->getId()}\" selected=\"selected\">{$calendar->getName()}</option>"; }
					else { echo "<option value=\"{$calendar->getId()}\">{$calendar->getName()}</option>"; }
				}
			?>
			</select>
		</td>
	</tr>

	<?php $start = $this->event->getStartDate() ? strtotime("{$this->event->getStartDate()} {$this->event->getStartTime()}") : time(); ?>
	<tr><td><label for="event-startDate">Start time</label></td>
		<td><input name="event[startDate]" id="event-startDate" size="10" maxlength="10" value="<?php echo date('n/j/Y',$start); ?>" />
			<input name="event[startTime]" id="event-startTime" size="7" maxlength="7" value="<?php echo date('g:ia',$start); ?>" />
			<?php $checked = $this->event->isAllDayEvent() ? 'checked="checked"' : ''; ?>
			<input name="allDayEvent" id="allDayEvent" type="checkbox" value="1" <?php echo $checked; ?> onclick="toggleTimes();" />
			<label for="allDayEvent">All Day Event</label>
		</td>
	</tr>
	<?php $end = $this->event->getEndDate() ? strtotime("{$this->event->getEndDate()} {$this->event->getEndTime()}") : strtotime('+1 hour',$start); ?>
	<tr><td><label for="event-endDate">End time</label></td>
		<td><input name="event[endDate]" id="event-endDate" size="10" maxlength="10" value="<?php echo date('n/j/Y',$end); ?>" />
			<input name="event[endTime]" id="event-endTime" size="7" maxlength="7" value="<?php echo date('g:ia',$end); ?>" />
		</td>
	</tr>

	<tr><td colspan="2">
			<div><label for="event-description">Description</label></div>
			<textarea name="event[description]" id="event-description" rows="3" cols="60"><?php echo $this->event->getDescription(); ?></textarea>
	</td></tr>

	</table>
</fieldset>

<fieldset><legend>Submit</legend>
		<input type="hidden" name="tab" id="tab" value="sections" />
		<input type="hidden" name="action" id="action" value="next" />
		<button type="submit" class="next">Next</button>
		<button type="cancel" class="cancel" onclick="self.close();">Cancel</button>
		<button type="button" class="save" onclick="processTabbedForm('eventForm','info','save');">Save</button>
</fieldset>
</form>
<script type="text/javascript">
	var startValue = document.getElementById("event-startTime").value;
	var endValue = document.getElementById("event-endTime").value;

	function toggleTimes()
	{
		var startTime = document.getElementById("event-startTime");
		var endTime = document.getElementById("event-endTime");

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
			document.getElementById("event-startTime").value = "";
			document.getElementById("event-endTime").value = "";
			document.getElementById("event-startTime").style.display = "none";
			document.getElementById("event-endTime").style.display = "none";
			';
		}
	?>
</script>
<?php print_r($_SESSION['event']); ?>
