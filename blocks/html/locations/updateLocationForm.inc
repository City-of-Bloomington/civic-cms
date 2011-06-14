<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Location $this->location
 * @param FacetGroupList $this->facetGroupList The facets the user is allowed to assign
 */
?>
<h1>Update Location</h1>
<form method="post" action="<?php echo $_SERVER['SCRIPT_NAME']; ?>">
<fieldset><legend>Location Info</legend>
	<input name="location_id" type="hidden" value="<?php echo $this->location->getId(); ?>" />
	<input name="return_url" type="hidden" value="<?php echo $this->return_url; ?>" />
	<table>

	<tr><td><label for="location-name" class="required">Name</label></td>
		<td><input name="location[name]" id="location-name" size="60" value="<?php echo View::escape($this->location->getName()); ?>" /></td></tr>
	<tr><td><label for="location-locationType_id" class="required">Type</label></td>
		<td><select name="location[locationType_id]" id="location-locationType_id">
			<?php
				$list = new LocationTypeList();
				$list->find();
				foreach($list as $type)
				{
					$selected = $this->location->getLocationType_id()==$type->getId() ? 'selected="selected"' : '';
					echo "<option value=\"{$type->getId()}\" $selected>$type</option>";
				}
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
						$selected = $this->location->getDepartment_id()==$department->getId() ? 'selected="selected"' : '';
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
		<td><input name="location[address]" id="location-address" size="60" value="<?php echo View::escape($this->location->getAddress()); ?>" /></td></tr>
	<tr><td><label for="location-phone">Phone</label></td>
		<td><input name="location[phone]" id="location-phone" size="60" value="<?php echo View::escape($this->location->getPhone()); ?>" /></td></tr>
	<tr><td><label for="location-latitude">Latitude</label></td>
		<td><input name="location[latitude]" id="location-latitude" size="60" value="<?php echo $this->location->getLatitude(); ?>" /></td></tr>
	<tr><td><label for="location-longitude">Longitude</label></td>
		<td><input name="location[longitude]" id="location-longitude" size="60" value="<?php echo $this->location->getLongitude(); ?>" /></td></tr>
	<tr><td><label>Handicap Accessible</label></td>
		<td><label>
				<?php $checked = $this->location->isHandicapAccessible() ? 'checked="checked"' : ''; ?>
				<input name="location[handicap_accessible]" id="location-handicap_accessible_yes" type="radio" value="1" <?php echo $checked; ?> />
				Yes
			</label>
			<label>
				<?php $checked = !$this->location->isHandicapAccessible() ? 'checked="checked"' : ''; ?>
				<input name="location[handicap_accessible]" id="location-handicap_accessible_no" type="radio" value="0" <?php echo $checked; ?> />
				No
			</label>
		</td>
	</tr>
	<tr><td colspan="2">
			<label for="location-description" class="required">Description</label>
			<textarea name="location[description]" id="location-description" rows="4" cols="60" onkeyup="FRAMEWORK.limit(this,350);"><?php echo View::escape($this->location->getDescription()); ?></textarea>
	</td></tr>
		<tr><td><label for="location-website">Website</label></td>
		<td><input name="location[website]" id="location-website" size="60" value="<?php echo View::escape($this->location->getWebsite()); ?>" /></td></tr>

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
			$checked = $this->location->hasGroup($group) ? 'checked="checked"' : '';
			echo "
			<label>
				<input name=\"location[locationGroups][{$group->getId()}]\" type=\"checkbox\" value=\"{$group->getId()}\" $checked />
				$group
			</label>
			";
		}
	?>
</fieldset>

<fieldset><legend>Facets</legend>
<?php
	foreach($this->facetGroupList as $group) {
		$name = View::escape($group->getName());
		echo "<h3>$name</h3>";

		foreach($group->getFacets() as $facet) {
			$facetName = View::escape($facet->getName());
			$checked = $this->location->hasFacet($facet) ? $checked = 'checked="checked"' : $checked = '';
			echo "
			<label>
				<input type=\"checkbox\" name=\"facets[{$facet->getId()}]\" value=\"{$facet->getId()}\" $checked />
				$facetName
			</label>
			";
		}
	}
?>
</fieldset>
<fieldset><legend>Web Content</legend>
	<script type="text/javascript">
	// This declares the function that will handle the return value from the
	// image browser.  The image browser will call this function with the
	// media_id of the image the user selected
	function handleSelection(media_id)
	{
		string = '[image:'+media_id+']';
		tinyMCE.execCommand('mceInsertContent',false,string);
	}
	</script>
	<div>
		<button type="button" class="browse" onclick="window.open('<?php echo BASE_URL; ?>/media/imageBrowser.php');">
			Browse Images
		</button>
		<button type="button" class="help" onclick="window.open('<?php echo BASE_URL; ?>/documents/notationGuide.php');">
			Notation Guide
		</button>
	</div>
	<?php
		$content = $this->location->getContent();
		$content_field_name = 'content';
		include APPLICATION_HOME.'/includes/editors/'.EDITOR.'/editor_init.inc';
	?>
</fieldset>
<fieldset><legend>Submit</legend>
	<button type="submit" class="submit">Submit</button>
	<a class="cancel" href="<?php echo $this->return_url; ?>">Cancel</a>
</fieldset>
</form>
