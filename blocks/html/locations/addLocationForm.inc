<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
?>
<h1>Add Location</h1>
<form method="post" action="<?php echo $_SERVER['PHP_SELF']; ?>">
<fieldset><legend>Location Info</legend>
	<table>

	<tr><td><label for="location-name" class="required">Name</label></td>
		<td><input name="location[name]" id="location-name" /></td></tr>
	<tr><td><label for="location-locationType_id" class="required">Type</label></td>
		<td><select name="location[locationType_id]" id="location-locationType_id">
			<?php
				$list = new LocationTypeList();
				$list->find();
				foreach($list as $type) { echo "<option value=\"{$type->getId()}\">$type</option>"; }
			?>
			</select>
		</td>
	</tr>
	<?php
		if (userHasRole(array('Administrator','Webmaster')))
		{
			echo "
			<tr><td><label for=\"department_id\">Department</label></td>
				<td><select name=\"department_id\" id=\"department_id\">
			";
					$list = new DepartmentList();
					$list->find();
					foreach($list as $department)
					{
						$name = View::escape($department->getName());
						$selected = $this->location->getDepartment_id()==$_SESSION['USER']->getDepartment_id() ? 'selected="selected"' : '';
						echo "<option value=\"{$department->getId()}\" $selected>$name</option>";
					}
			echo "
					</select>
				</td>
			</tr>
			";
		}
	?>
	<tr><td><label for="location-address" class="required">Address</label></td>
		<td><input name="location[address]" id="location-address" /></td></tr>
	<tr><td><label for="location-latitude">Latitude</label></td>
		<td><input name="location[latitude]" id="location-latitude" /></td></tr>
	<tr><td><label for="location-longitude">Longitude</label></td>
		<td><input name="location[longitude]" id="location-longitude" /></td></tr>
	<tr><td colspan="2">
			<label for="location-description" class="required">Description</label>
			<textarea name="location[description]" id="location-description" rows="3" cols="60"></textarea>
	</td></tr>

	</table>
</fieldset>
<fieldset><legend>Groups</legend>
	<p>Choose groups to put this location into:</p>
	<?php
		$list = new LocationGroupList();
		if (userHasRole(array('Administrator','Webmaster'))) { $list->find(); }
		else { $list->find(array('department_id'=>$_SESSION['USER']->getDepartment_id())); }

		foreach($list as $group)
		{
			echo "
			<label>
				<input name=\"location[locationGroups][{$group->getId()}]\" type=\"checkbox\" value=\"{$group->getId()}\" />
				$group
			</label>
			";
		}
	?>
</fieldset>
<fieldset><legend>Directions</legend>
	<?php
		include APPLICATION_HOME.'/html/editors/fckeditor/FCKeditor.php';
		$FCKeditor = new FCKeditor("directions");
		$FCKeditor->BasePath = BASE_URL.'/editors/fckeditor/';
		$FCKeditor->ToolbarSet = 'Custom';

		$FCKeditor->create();
	?>
</fieldset>
<fieldset><legend>Submit</legend>
	<button type="submit" class="submit">Submit</button>
	<button type="button" class="cancel" onclick="document.location.href='<?php echo BASE_URL; ?>/locations';">Cancel</button>
</fieldset>
</form>
