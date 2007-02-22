<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param int $this->calendar_id
 */
?>
<h1>Add Event</h1>
<form method="post" action="<?php echo $_SERVER['PHP_SELF']; ?>">
<fieldset><legend>Event Info</legend>
	<table>

	<tr><td><label for="event-summary">Summary</label></td>
		<td><input name="event[summary]" id="event-summary" /></td></tr>

	<tr><td><label for="event-start-mon">Start</label></td>
		<td><select name="event[start][mon]" id="event-start-mon"><option></option>
			<?php
				$now = getdate();
				for($i=1; $i<=12; $i++)
				{
					if ($i!=$now['mon']) { echo "<option>$i</option>"; }
					else { echo "<option selected=\"selected\">$i</option>"; }
				}
			?>
			</select>
			<select name="event[start][mday]"><option></option>
			<?php
				for($i=1; $i<=31; $i++)
				{
					if ($i!=$now['mday']) { echo "<option>$i</option>"; }
					else { echo "<option selected=\"selected\">$i</option>"; }
				}
			?>
			</select>
			<input name="event[start][year]" id="event-start-year" size="4" maxlength="4" value="<?php echo $now['year']; ?>" />
			<select name="event[start][hours]" id="event-start-hours">
			<?php
				for($i=0; $i<=23; $i++)
				{
					if ($i!=$now['hours']) { echo "<option>$i</option>"; }
					else { echo "<option selected=\"selected\">$i</option>"; }
				}
			?>
			</select>
			<select name="event[start][minutes]" id="event-start-minutes">
			<?php
				for($i=0; $i<=59; $i+=15)
				{
					if ($i!=$now['minutes']) { echo "<option>$i</option>"; }
					else { echo "<option selected=\"selected\">$i</option>"; }
				}
			?>
			</select>
		</td>
	</tr>
	<tr><td><label for="event-end-mon">End</label></td>
		<td><select name="event[end][mon]" id="event-end-mon"><option></option>
			<?php
				$now = getdate();
				for($i=1; $i<=12; $i++)
				{
					if ($i!=$now['mon']) { echo "<option>$i</option>"; }
					else { echo "<option selected=\"selected\">$i</option>"; }
				}
			?>
			</select>
			<select name="event[end][mday]"><option></option>
			<?php
				for($i=1; $i<=31; $i++)
				{
					if ($i!=$now['mday']) { echo "<option>$i</option>"; }
					else { echo "<option selected=\"selected\">$i</option>"; }
				}
			?>
			</select>
			<input name="event[end][year]" id="event-end-year" size="4" maxlength="4" value="<?php echo $now['year']; ?>" />
			<select name="event[end][hours]" id="event-end-hours">
			<?php
				for($i=0; $i<=23; $i++)
				{
					if ($i!=$now['hours']) { echo "<option>$i</option>"; }
					else { echo "<option selected=\"selected\">$i</option>"; }
				}
			?>
			</select>
			<select name="event[end][minutes]" id="event-end-minutes">
			<?php
				for($i=0; $i<=59; $i+=15)
				{
					if ($i!=$now['minutes']) { echo "<option>$i</option>"; }
					else { echo "<option selected=\"selected\">$i</option>"; }
				}
			?>
			</select>
		</td>
	</tr>
	<tr><td><label for="event-description">Description</label></td>
		<td><textarea name="event[description]" id="event-description" rows="3" cols="60"></textarea></td></tr>

	<tr><td><label for="event-calendar_id">Calendar</label></td>
		<td><select name="event[calendar_id]" id="event-calendar_id">
			<?php
				$list = new CalendarList();
				$list->find();
				foreach($list as $calendar)
				{
					if (isset($this->calendar_id) && $this->calendar_id == $calendar->getId())
					{
						echo "<option value=\"{$calendar->getId()}\" selected=\"selected\">{$calendar->getName()}</option>";
					}
					else { echo "<option value=\"{$calendar->getId()}\">{$calendar->getName()}</option>"; }
				}
			?>
			</select>
		</td>
	</tr>

	<tr><td><label for="event-location_id">Location</label></td>
		<td><select name="event[location_id]" id="event-location">
			<?php
				$list = new LocationList();
				$list->find();
				foreach($list as $location) { echo "<option value=\"{$location->getId()}\">$location</option>"; }
			?>
			</select>
		</td></tr>


	</table>
</fieldset>

<fieldset><legend>Sections</legend>
	<table>
	<?php
		$sections = new SectionList();
		if (userHasRole(array('Administrator','Webmaster'))) { $sections->find(); }
		else { $sections->find(array('department_id'=>$_SESSION['USER']->getDepartment_id())); }

		foreach($sections as $section)
		{
			echo "
			<tr><td><input name=\"event[sections][{$section->getId()}]\" id=\"event-sections-{$section->getId()}\" type=\"checkbox\" value=\"{$section->getId()}\" /></td>
				<td><label for=\"event-sections-{$section->getId()}\">{$section}</label></td></tr>
			";
		}
	?>
	</table>
</fieldset>

<fieldset><legend>Submit</legend>
	<button type="submit" class="submit">Submit</button>
	<button type="button" class="cancel" onclick="document.location.href='<?php echo BASE_URL; ?>/calendars';">Cancel</button>
</fieldset>
</form>