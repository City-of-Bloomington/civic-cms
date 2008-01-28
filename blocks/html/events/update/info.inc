<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Event $this->event
 * @param URL $this->return_url
 * @param int $this->instance_id
 */
?>
<form id="eventForm" method="post" action="<?php echo $_SERVER['PHP_SELF']; ?>">
<fieldset><legend>Event Info</legend>
	<table>
	<tr><td><label for="event-title" class="required">Title</label></td>
		<td><input name="event[title]" id="event-title" size="60" value="<?php echo $this->event->getTitle(); ?>" /></td></tr>

	<tr><td><label for="event-location_id">Location</label></td>
		<td><select name="event[location_id]" id="event-location_id">
			<?php
				$list = new LocationList();
				$list->find();
				foreach($list as $location)
				{
					$name = View::escape($location->getName());
					$selected = ($this->event->getLocation_id() === $location->getId()) ? 'selected="selected"' : '';
					echo "<option value=\"{$location->getId()}\" $selected>$name</option>";
				}
			?>
			</select>
		</td>
	</tr>


	<tr><td><label for="event-calendar_id" class="required">Calendar</label></td>
		<td><select name="event[calendar_id]" id="event-calendar_id">
			<?php
				$list = new CalendarList();
				$list->find();
				foreach($list as $calendar)
				{
					$name = View::escape($calendar->getName());
					$selected = ($this->event->getCalendar_id() === $calendar->getId()) ? 'selected="selected"' : '';
					echo "<option value=\"{$calendar->getId()}\" $selected>$name</option>";
				}
			?>
			</select>
		</td>
	</tr>

	<?php $start = $this->event->getStart() ? $this->event->getStart() : time(); ?>
	<tr><td><label for="startDate" class="required">Start time</label></td>
		<td><input name="startDate" id="startDate" size="10" maxlength="10" value="<?php echo date('n/j/Y',$start); ?>" />
			<input name="startTime" id="startTime" size="7" maxlength="7" value="<?php echo date('g:ia',$start); ?>" />
			<?php $checked = $this->event->isAllDayEvent() ? 'checked="checked"' : ''; ?>
			<input name="allDayEvent" id="allDayEvent" type="checkbox" value="1" <?php echo $checked; ?> onclick="toggleTimes();" />
			<label for="allDayEvent">All Day Event</label>
		</td>
	</tr>
	<?php $end = $this->event->getEnd() ? $this->event->getEnd() : strtotime('+1 hour',$start); ?>
	<tr><td><label for="endDate">End time</label></td>
		<td><input name="endDate" id="endDate" size="10" maxlength="10" value="<?php echo date('n/j/Y',$end); ?>" />
			<input name="endTime" id="endTime" size="7" maxlength="7" value="<?php echo date('g:ia',$end); ?>" />
		</td>
	</tr>
	</table>
</fieldset>

<fieldset><legend>Contact Info</legend>
	<p>You can enter contact info, or select a person from the list.  Selecting a person from the list will
		enter their info into the form.</p>
	<table>
	<tr><td><label for="content_manager_username">Contact Person</label></td>
		<td><select name="content_manager_username" id="content_manager_username" onchange="updateContactInfo(this.options[this.selectedIndex].value);"><option></option>
			<?php
				foreach($_SESSION['USER']->getDepartment()->getUsers() as $user)
				{
					$firstname = View::escape($user->getFirstname());
					$lastname = View::escape($user->getLastname());
					echo "<option value=\"{$user->getUsername()}\">$firstname $lastname</option>";
				}
			?>
			</select>
			<button type="button" class="button" onclick="toggleLDAPList(this);">Show Full List</button>
			<select name="ldap_username" id="ldap_username" style="display:none;" onchange="updateContactInfo(this.options[this.selectedIndex].value);"><option></option>
			<?php
				$ldap = new SimpleXMLElement('http://isotope.bloomington.in.gov/directory/viewCategory.php?category=City%20Hall;format=xml',null,true);
				foreach($ldap as $department)
				{
					$department_name = View::escape($department['name']);
					echo "<option value=\"\">$department_name</option>";
					foreach($department as $office)
					{
						$office_name = View::escape($office['name']);
						echo "<option value=\"\"> - $office_name</option>";
						foreach($office as $person)
						{
							$person_name = View::escape($person->name);
							echo "<option value=\"{$person->username}\"> - - $person_name</option>";
						}
					}
				}
			?>
			</select>
		</td>
	</tr>
	<tr><td><label for="event-contact_name">Name</label></td>
		<td><input name="event[contact_name]" id="event-contact_name" size="30" value="<?php echo View::escape($this->event->getContact_name()); ?>" /></td></tr>
	<tr><td><label for="event-contact_phone">Phone</label></td>
		<td><input name="event[contact_phone]" id="event-contact_phone" size="12" value="<?php echo View::escape($this->event->getContact_phone()); ?>" /></td></tr>
	<tr><td><label for="event-contact_email">Email</label></td>
		<td><input name="event[contact_email]" id="event-contact_email" size="60" value="<?php echo View::escape($this->event->getContact_email()); ?>" /></td></tr>
	</table>
</fieldset>
<?php
	$freq = $this->event->getRrule_freq();
	$interval = $this->event->getRrule_interval();
	$byday = $this->event->getRrule_byday() ? explode(',',$this->event->getRrule_byday()) : array();
	$weekdaynum = isset($byday[0]) ? substr($byday[0],0,-2) : '';
	$bymonthday = isset($rrule['BYMONTHDAY']) ? $rrule['BYMONTHDAY'] : '';

?>
<fieldset><legend>Recurrence</legend>
	<label><input name="freq" type="radio" value="" onclick="activate('none');" <?php if($freq=='') echo 'checked="checked"'; ?> />None</label>
	<label><input name="freq" type="radio" value="DAILY" onclick="activate('daily');" <?php if($freq=='DAILY') echo 'checked="checked"'; ?> />Daily</label>
	<label><input name="freq" type="radio" value="WEEKLY" onclick="activate('weekly');" <?php if($freq=='WEEKLY') echo 'checked="checked"'; ?> />Weekly</label>
	<label><input name="freq" type="radio" value="MONTHLY" onclick="activate('monthly');" <?php if($freq=='MONTHLY') echo 'checked="checked"'; ?> />Monthly</label>
</fieldset>

<fieldset id="daily" <?php if($freq!='DAILY') echo 'style="display:none;"'; ?>>
	<label>Every <input name="daily_interval" size="1" value="<?php echo $interval; ?>" /> days</label>
</fieldset>

<fieldset id="weekly" <?php if($freq!='WEEKLY') echo 'style="display:none;"'; ?>>
	<div><label>Every <input name="weekly_interval" size="1" value="<?php echo $interval; ?>" /> weeks</label></div>
	<div>
		<label><input name="weekly[BYDAY][SU]" type="checkbox" <?php if(in_array('SU',$byday)) echo 'checked="checked"'; ?> />Sunday</label>
		<label><input name="weekly[BYDAY][MO]" type="checkbox" <?php if(in_array('MO',$byday)) echo 'checked="checked"'; ?> />Monday</label>
		<label><input name="weekly[BYDAY][TU]" type="checkbox" <?php if(in_array('TU',$byday)) echo 'checked="checked"'; ?> />Tuesday</label>
		<label><input name="weekly[BYDAY][WE]" type="checkbox" <?php if(in_array('WE',$byday)) echo 'checked="checked"'; ?> />Wednesday</label>
		<label><input name="weekly[BYDAY][TH]" type="checkbox" <?php if(in_array('TH',$byday)) echo 'checked="checked"'; ?> />Thursday</label>
		<label><input name="weekly[BYDAY][FR]" type="checkbox" <?php if(in_array('FR',$byday)) echo 'checked="checked"'; ?> />Friday</label>
		<label><input name="weekly[BYDAY][SA]" type="checkbox" <?php if(in_array('SA',$byday)) echo 'checked="checked"'; ?> />Saturday</label>
	</div>
</fieldset>

<fieldset id="monthly" <?php if($freq!='MONTHLY') echo 'style="display:none;"'; ?>>
	<div><input name="monthly_type" type="radio" value="BYMONTHDAY" <?php if($bymonthday || !$byday) echo 'checked="checked"'; ?> />
			<label>Day <input name="bymonthday" size="2" value="<?php if($bymonthday) echo $bymonthday; else echo 30; ?>" /></label>
			<label>of every <input name="bymonthday_interval" size="1" value="<?php echo $interval; ?>" /> month</label>
	</div>
	<div><input name="monthly_type" type="radio" value="BYDAY" <?php if($byday) echo 'checked="checked"'; ?> />
			<label>The
				<select name="offset">
					<option value="1" <?php if($weekdaynum==1) echo 'selected="selected"'; ?>>First</option>
					<option value="2" <?php if($weekdaynum==2) echo 'selected="selected"'; ?>>Second</option>
					<option value="3" <?php if($weekdaynum==3) echo 'selected="selected"'; ?>>Third</option>
					<option value="4" <?php if($weekdaynum==4) echo 'selected="selected"'; ?>>Fourth</option>
					<option value="-2" <?php if($weekdaynum==-2) echo 'selected="selected"'; ?>>Second to Last</option>
					<option value="-1" <?php if(!$weekdaynum || $weekdaynum==-1) echo 'selected="selected"'; ?>>Last</option>
				</select>
			</label>
			<label>
				<select name="monthly_byday">
					<?php
						$weekday = isset($byday[0]) ? substr($byday[0],-2) : '';
					?>
					<option value="SU" <?php if($weekday=='SU') echo 'selected="selected"'; ?>>Sunday</option>
					<option value="MO" <?php if($weekday=='MO') echo 'selected="selected"'; ?>>Monday</option>
					<option value="TU" <?php if($weekday=='TU') echo 'selected="selected"'; ?>>Tuesday</option>
					<option value="WE" <?php if($weekday=='WE') echo 'selected="selected"'; ?>>Wednesday</option>
					<option value="TH" <?php if($weekday=='TH') echo 'selected="selected"'; ?>>Thursday</option>
					<option value="FR" <?php if($weekday=='FR') echo 'selected="selected"'; ?>>Friday</option>
					<option value="SA" <?php if($weekday=='SA') echo 'selected="selected"'; ?>>Saturday</option>
				</select>
				of every
			</label>
			<label><input name="monthly_interval" size="1" value="<?php echo $interval; ?>" /> month</label>
	</div>
</fieldset>

<fieldset id="until_fields" <?php if (!$freq) echo 'style="display:none;"'; ?>>
	<?php
		if ($this->event->getRrule_count()) { $rrule_end_type = 'count'; }
		elseif($this->event->getRrule_until()) { $rrule_end_type = 'until'; }
		else { $rrule_end_type = 'none'; }

		$count = $this->event->getRrule_count() ? $this->event->getRrule_count() : 10;
		$until = $this->event->getRrule_until() ? $this->event->getRrule_until() : strtotime('+2 weeks');
	?>
	<div><label><input type="radio" name="rrule_end_type" value="none" <?php if($rrule_end_type=='none') echo 'checked="checked"'; ?> />No end date</label></div>
	<div><label><input type="radio" name="rrule_end_type" value="count" <?php if($rrule_end_type=='count') echo 'checked="checked"'; ?> />End after</label>
		<label><input name="count" value="<?php echo $count; ?>" />occurances</label>
	</div>
	<div><label><input type="radio" name="rrule_end_type" value="until" <?php if($rrule_end_type=='until') echo 'checked="checked"'; ?> />End by</label>
		<input name="until" value="<?php echo date('n/j/Y',$until); ?>" />
	</div>
</fieldset>

<fieldset><legend>Submit</legend>
		<input type="hidden" name="tab" id="tab" value="description" />
		<input type="hidden" name="action" id="action" value="next" />
		<input type="hidden" name="continue" id="continue" value="true" />
		<input type="hidden" name="return_url" id="return_url" value="<?php echo $this->return_url; ?>" />
		<input type="hidden" name="instance_id" id="instance_id" value="<?php echo $this->instance_id; ?>" />
		<button type="submit" class="next">Next</button>
		<button type="button" class="cancel" onclick="document.location.href='<?php echo $this->return_url; ?>';">Cancel</button>
		<button type="button" class="save" onclick="FRAMEWORK.processTabbedForm('eventForm','info','save');">Save</button>
</fieldset>
</form>
<script type="text/javascript">
	var startTime = document.getElementById("startTime");
	var endTime = document.getElementById("endTime");
	var LDAPSelect = document.getElementById('ldap_username');

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

	function toggleLDAPList(button)
	{
		if (LDAPSelect.style.display == 'none')
		{
			LDAPSelect.style.display = '';
			button.firstChild.nodeValue = 'Hide Full List';
		}
		else
		{
			LDAPSelect.style.display = 'none';
			button.firstChild.nodeValue = 'Show Full List';
		}
	}

	function updateContactInfo(username)
	{
		if (username)
		{
			document.getElementById('event-contact_name').value = people[username].name;
			document.getElementById('event-contact_phone').value = people[username].phone;
			document.getElementById('event-contact_email').value = people[username].email;
		}
	}

	function activate(field)
	{
		document.getElementById("daily").style.display = "none";
		document.getElementById("weekly").style.display = "none";
		document.getElementById("monthly").style.display = "none";
		if (field != 'none')
		{
			document.getElementById(field).style.display = "block";
			document.getElementById('until_fields').style.display = "block";
		}
		else { document.getElementById('until_fields').style.display = "none"; }
	}

	var people = {};
	<?php
		$people = array();
		foreach($ldap->xpath('//person') as $person)
		{
			$name = htmlspecialchars($person->name,ENT_QUOTES);
			$title = htmlspecialchars($person->title,ENT_QUOTES);
			$phone = htmlspecialchars($person->phone,ENT_QUOTES);
			$email = htmlspecialchars($person->email,ENT_QUOTES);
			echo "people.{$person->username} = {'name':'$name','title':'$title','phone':'$phone','email':'$email'}\n\t";
		}
	?>
</script>
