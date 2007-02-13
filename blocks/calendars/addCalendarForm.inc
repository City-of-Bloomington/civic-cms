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

	<tr><td><label for="calendar-name">Name</label></td>
		<td><input name="calendar[name]" id="calendar-name" /></td></tr>

	<tr><td><label for="calendar-department_id">Name</label></td>
		<td><select name="calendar[department_id]" id="calendar-department_id">
			<?php
				$list = new DepartmentList();
				$list->find();
				foreach($list as $department) { echo "<option value=\"{$department->getId()}\">$department</option>"; }
			?>
			</select>
		</td>
	</tr>
	</table>

	<button type="submit" class="submit">Submit</button>
	<button type="button" class="cancel" onclick="document.location.href='<?php echo BASE_URL; ?>/calendars';">Cancel</button>
</fieldset>
</form>