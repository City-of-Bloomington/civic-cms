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
<script type="text/javascript">
	function activate(field)
	{
		document.getElementById("daily").style.display = "none";
		document.getElementById("weekly").style.display = "none";
		document.getElementById("monthly").style.display = "none";
		if (field != 'none') document.getElementById(field).style.display = "block";
	}
</script>
<form id="eventForm" method="post" action="<?php echo $_SERVER['PHP_SELF']; ?>">
<fieldset><legend>Pattern</legend>
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
		<input type="hidden" name="tab" id="tab" value="info" />
		<input type="hidden" name="action" id="action" value="next" />
		<button type="submit" class="next">Next</button>
		<button type="cancel" class="cancel" onclick="self.close();">Cancel</button>
		<button type="button" class="save" onclick="FRAMEWORK.processTabbedForm('eventForm','recurrance','save');">Save</button>
</fieldset>
</form>
