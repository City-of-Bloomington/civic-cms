<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Event $this->event
 */
	$rrule = $this->event->getRRuleArray();
	$freq = isset($rrule['FREQ']) ? $rrule['FREQ'] : '';
	$interval = isset($rrule['INTERVAL']) ? $rrule['INTERVAL'] : 1;
	$byday = isset($rrule['BYDAY']) ? $rrule['BYDAY'] : array();
	$weekdaynum = isset($byday[0]) ? substr($byday[0],0,-2) : '';
	$bymonthday = isset($rrule['BYMONTHDAY']) ? $rrule['BYMONTHDAY'] : '';
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
					$selected = ($this->event->getLocation_id() === $location->getId()) ? 'selected="selected"' : '';
					echo "<option value=\"{$location->getId()}\" $selected>$location</option>";
				}
			?>
			</select>
		</td>
	</tr>

	<tr><td><label for="event-contact_id">Contact Person</label></td>
		<td><select name="event[contact_id]" id="event-contact_id"><option></option>
			<?php
				foreach($_SESSION['USER']->getDepartment()->getUsers() as $user)
				{
					$selected = ($this->event->getContact_id() === $user->getId()) ? 'selected="selected"' : '';
					echo "<option value=\"{$user->getId()}\" $selected>{$user->getLastname()}, {$user->getFirstname()}</option>";
				}
			?>
			</select>
			<button type="button" class="button" onclick="toggleFullContactList(this);">Show Full List</button>
			<select name="contact_id" id="contact_id" style="display:none;"><option></option>
			<?php
				$list = new UserList();
				$list->find();
				foreach($list as $user)
				{
					$selected = ($this->event->getContact_id() === $user->getId()) ? 'selected="selected"' : '';
					echo "<option value=\"{$user->getId()}\" $selected>{$user->getLastname()}, {$user->getFirstname()}</option>";
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
					$selected = ($this->event->getCalendar_id() === $calendar->getId()) ? 'selected="selected"' : '';
					echo "<option value=\"{$calendar->getId()}\" $selected>{$calendar->getName()}</option>";
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

<fieldset><legend>Recurrence</legend>
	<label><input name="event[RRule][FREQ]" type="radio" value="" onclick="activate('none');" <?php if($freq=='') echo 'checked="checked"'; ?> />None</label>
	<label><input name="event[RRule][FREQ]" type="radio" value="DAILY" onclick="activate('daily');" <?php if($freq=='DAILY') echo 'checked="checked"'; ?> />Daily</label>
	<label><input name="event[RRule][FREQ]" type="radio" value="WEEKLY" onclick="activate('weekly');" <?php if($freq=='WEEKLY') echo 'checked="checked"'; ?> />Weekly</label>
	<label><input name="event[RRule][FREQ]" type="radio" value="MONTHLY" onclick="activate('monthly');" <?php if($freq=='MONTHLY') echo 'checked="checked"'; ?> />Monthly</label>
</fieldset>

<fieldset id="daily" <?php if($freq!='DAILY') echo 'style="display:none;"'; ?>>
	<label>Every <input name="event[RRule][DAILY][INTERVAL]" size="1" value="<?php echo $interval; ?>" /> days</label>
</fieldset>

<fieldset id="weekly" <?php if($freq!='WEEKLY') echo 'style="display:none;"'; ?>>
	<div><label>Every <input name="event[RRule][WEEKLY][INTERVAL]" size="1" value="<?php echo $interval; ?>" /> weeks</label></div>
	<div>
		<label><input name="event[RRule][WEEKLY][BYDAY][SU]" type="checkbox" <?php if(in_array('SU',$byday)) echo 'checked="checked"'; ?> />Sunday</label>
		<label><input name="event[RRule][WEEKLY][BYDAY][MO]" type="checkbox" <?php if(in_array('MO',$byday)) echo 'checked="checked"'; ?> />Monday</label>
		<label><input name="event[RRule][WEEKLY][BYDAY][TU]" type="checkbox" <?php if(in_array('TU',$byday)) echo 'checked="checked"'; ?> />Tuesday</label>
		<label><input name="event[RRule][WEEKLY][BYDAY][WE]" type="checkbox" <?php if(in_array('WE',$byday)) echo 'checked="checked"'; ?> />Wednesday</label>
		<label><input name="event[RRule][WEEKLY][BYDAY][TH]" type="checkbox" <?php if(in_array('TH',$byday)) echo 'checked="checked"'; ?> />Thursday</label>
		<label><input name="event[RRule][WEEKLY][BYDAY][FR]" type="checkbox" <?php if(in_array('FR',$byday)) echo 'checked="checked"'; ?> />Friday</label>
		<label><input name="event[RRule][WEEKLY][BYDAY][SA]" type="checkbox" <?php if(in_array('SA',$byday)) echo 'checked="checked"'; ?> />Saturday</label>
	</div>
</fieldset>

<fieldset id="monthly" <?php if($freq!='MONTHLY') echo 'style="display:none;"'; ?>>
	<div><input name="event[RRule][MONTHLY][type]" type="radio" value="BYMONTHDAY" <?php if($bymonthday) echo 'checked="checked"'; ?> />
			<label>Day <input name="event[RRule][MONTHLY][BYMONTHDAY][DAYNUM]" size="2" value="<?php if($bymonthday) echo $bymonthday; else echo 30; ?>" /></label>
			<label>of every <input name="event[RRule][MONTHLY][BYMONTHDAY][INTERVAL]" size="1" value="<?php echo $interval; ?>" /> month</label>
	</div>
	<div><input name="event[RRule][MONTHLY][type]" type="radio" value="BYDAY" <?php if($byday) echo 'checked="checked"'; ?> />
			<label>The
				<select name="event[RRule][MONTHLY][BYDAY][weekdaynum]">
					<option value="1" <?php if($weekdaynum==1) echo 'selected="selected"'; ?>>First</option>
					<option value="2" <?php if($weekdaynum==2) echo 'selected="selected"'; ?>>Second</option>
					<option value="3" <?php if($weekdaynum==3) echo 'selected="selected"'; ?>>Third</option>
					<option value="4" <?php if($weekdaynum==4) echo 'selected="selected"'; ?>>Fourth</option>
					<option value="-2" <?php if($weekdaynum==-2) echo 'selected="selected"'; ?>>Second to Last</option>
					<option value="-1" <?php if(!$weekdaynum || $weekdaynum==-1) echo 'selected="selected"'; ?>>Last</option>
				</select>
			</label>
			<label>
				<select name="event[RRule][MONTHLY][BYDAY][weekday]">
					<option value="SU" <?php if(in_array('SU',$byday)) echo 'selected="selected"'; ?>>Sunday</option>
					<option value="MO" <?php if(in_array('MO',$byday)) echo 'selected="selected"'; ?>>Monday</option>
					<option value="TU" <?php if(in_array('TU',$byday)) echo 'selected="selected"'; ?>>Tuesday</option>
					<option value="WE" <?php if(in_array('WE',$byday)) echo 'selected="selected"'; ?>>Wednesday</option>
					<option value="TH" <?php if(in_array('TH',$byday)) echo 'selected="selected"'; ?>>Thursday</option>
					<option value="FR" <?php if(in_array('FR',$byday)) echo 'selected="selected"'; ?>>Friday</option>
					<option value="SA" <?php if(in_array('SA',$byday)) echo 'selected="selected"'; ?>>Saturday</option>
				</select>
				of every
			</label>
			<label><input name="event[RRule][MONTHLY][BYDAY][INTERVAL]" size="1" value="<?php echo $interval; ?>" /> month</label>
	</div>
</fieldset>

<fieldset><legend>Submit</legend>
		<input type="hidden" name="tab" id="tab" value="sections" />
		<input type="hidden" name="action" id="action" value="next" />
		<button type="submit" class="next">Next</button>
		<button type="cancel" class="cancel" onclick="self.close();">Cancel</button>
		<button type="button" class="save" onclick="FRAMEWORK.processTabbedForm('eventForm','info','save');">Save</button>
</fieldset>
</form>
<script type="text/javascript">
	var startTime = document.getElementById("event-startTime");
	var endTime = document.getElementById("event-endTime");
	var contact_id = document.getElementById("contact_id");

	<?php
		if ($this->event->isAllDayEvent())
		{
			echo '
			startTime.value = "";
			endTime.value = "";
			startTime.style.display = "none";
			endTime.style.display = "none";
			';
		}
	?>

	function toggleTimes()
	{
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

	function toggleFullContactList(button)
	{
		if (contact_id.style.display == 'none')
		{
			contact_id.style.display = '';
			button.firstChild.nodeValue = 'Hide Full List';
		}
		else
		{
			contact_id.style.display = 'none';
			button.firstChild.nodeValue = 'Show Full List';
		}
	}

	function activate(field)
	{
		document.getElementById("daily").style.display = "none";
		document.getElementById("weekly").style.display = "none";
		document.getElementById("monthly").style.display = "none";
		if (field != 'none') document.getElementById(field).style.display = "block";
	}
</script>
<?php print_r($this->event); ?>