<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param LocationGroup $this->locationGroup
 */
?>
<h1>Update Location Group</h1>
<form method="post" action="<?php echo $_SERVER['PHP_SELF']; ?>">
<fieldset><legend>LocationGroup Info</legend>
	<input name="id" type="hidden" value="<?php echo $this->locationGroup->getId(); ?>" />

	<table>
	<tr><td><label for="locationGroup-name" class="required">Name</label></td>
		<td><input name="locationGroup[name]" id="locationGroup-name" value="<?php echo $this->locationGroup->getName(); ?>" /></td></tr>
	<tr><td><label for="locationGroup-department_id" class="required">Department</label></td>
		<td><select name="locationGroup[department_id]" id="locationGroup-department_id">
			<?php
				$list = new DepartmentList();
				$list->find();
				foreach($list as $department)
				{
					$name = View::escape($department->getName());
					$selected = $this->locationGroup->getDepartment_id()==$department->getId() ? 'selected="selected"' : '';
					echo "<option value=\"{$department->getId()}\" $selected>$name</option>";
				}
			?>
			</select>
		</td>
	</tr>
	</table>

	<button type="submit" class="submit">Submit</button>
	<button type="button" class="cancel" onclick="document.location.href='<?php echo BASE_URL; ?>/locations';">Cancel</button>
</fieldset>
</form>
