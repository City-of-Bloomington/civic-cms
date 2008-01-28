<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
?>
<h1>Add Calendar</h1>
<form method="post" action="<?php echo $_SERVER['PHP_SELF']; ?>">
<fieldset><legend>Calendar Info</legend>
	<table>
	<tr><td><label for="calendar-name" class="required">Name</label></td>
		<td><input name="calendar[name]" id="calendar-name" size="60" /></td></tr>
	<tr><td colspan="2">
			<label for="calendar-description" class="required">Description</label>
			<textarea name="calendar[description]" id="calendar-description" rows="3" cols="60"></textarea>
	</td></tr>
	</table>
</fieldset>

<fieldset><legend>Departments</legend>
	<table>
	<?php
		$list = new DepartmentList();
		$list->find();
		foreach($list as $department)
		{
			$name = View::escape($department->getName());
			echo "
			<tr><td><input name=\"calendar[departments][{$department->getId()}]\" id=\"calendar-departments-{$department->getId()}\" type=\"checkbox\" value=\"{$department->getId()}\" /></td>
				<td><label for=\"calendar-departments-{$department->getId()}\">$name</label></td></tr>
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
