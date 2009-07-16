<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param LocationGroup $this->locationGroup
 */
?>
<h1>Update Location Group</h1>
<form method="post" action="<?php echo $_SERVER['SCRIPT_NAME']; ?>">
<fieldset><legend>LocationGroup Info</legend>
	<input name="id" type="hidden" value="<?php echo $this->locationGroup->getId(); ?>" />

	<table>
	<tr><td><label for="locationGroup-name" class="required">Name</label></td>
		<td><input name="locationGroup[name]" id="locationGroup-name" size="60" value="<?php echo $this->locationGroup->getName(); ?>" /></td></tr>
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
	<tr><td><label for="locationGroup-defaultFlag">Default</label></td>
		<td><input name="locationGroup[defaultFlag]"
					id="locationGroup-defaultFlag"
					type="checkbox"
					<?php echo $this->locationGroup->isDefault() ? 'checked="checked"' : ''; ?> />
			Makes this group displayed, by default, on the locations map.
		</td>
	</tr>
	</table>
</fieldset>

<fieldset><legend>Description</legend>
	<?php
		$content = $this->locationGroup->getDescription();
		$content_field_name = 'description';
		include APPLICATION_HOME.'/includes/editors/'.EDITOR.'/editor_init.inc';
	?>
</fieldset>

<fieldset><legend>Submit</legend>
	<button type="submit" class="submit">Submit</button>
	<a class="cancel" href="<?php echo BASE_URL; ?>/locations">Cancel</a>
</fieldset>
</form>
