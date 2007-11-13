<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Widget $this->widget
 */
?>
<fieldset><legend>Upcoming Events Settings</legend>
<p>Choose which calendar to pull events from.</p>
<label>Calendar
	<select name="calendar_id"><option value="">All Calendars</option>
	<?php
		$list = new CalendarList();
		$list->find();
		foreach($list as $calendar)
		{
			$calendar_id = $this->widget->calendar_id;
			$name = View::escape($calendar->getName());
			$selected = ($calendar_id==$calendar->getId()) ? 'selected="selected"' : '';
			echo "<option value=\"{$calendar->getId()}\" $selected>$name</option>";
		}
	?>
	</select>
</label>

<p>For how many days ahead do you want to show events?</p>
<label>Number of Days
	<select name="numDays">
	<?php
		for($i=1; $i<=10; $i++)
		{
			$numDays = $this->widget->numDays;
			$selected = ($numDays == $i) ? 'selected="selected"' : '';
			echo "<option $selected>$i</option>";
		}
	?>
	</select>
</label>

<p>Do you want this to display events only from the document's sections?</p>
<label><input name="isSectionBased" type="radio" value="true" <?php if($this->widget->isSectionBased) echo 'checked="checked"'; ?> />Yes</label>
<label><input name="isSectionBased" type="radio" value="false" <?php if(!$this->widget->isSectionBased) echo 'checked="checked"'; ?> />No</label>

</fieldset>
