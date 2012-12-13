<?php
/**
 * @copyright 2006-2012 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param LocationList $this->locationList
 * @param string $this->title
 * @param LocationGroup $this->locationGroup
 */
?>
<p>Use this feature to find locations grouped together into categories, such as City Facilities or Historic Sites.
Using GoogleMap technology, you can find the position of different locations all across the city,
as well as find driving directions, and information specific to a certain site.</p>
<h2>Select a Map</h2>
<form method="get" action="<?php echo BASE_URL; ?>/locations">
<fieldset>
	<label for="locationGroup_id">Select a Map</label>
	<select name="locationGroup_id" id="locationGroup_id" onchange="this.form.submit();">
		<option value="">Please make a selection</option>
	<?php
		$list = new LocationGroupList();
		$list->find();
		foreach($list as $group)
		{
			$name = View::escape($group->getName());
			$selected = (isset($this->locationGroup) && $this->locationGroup->getId()==$group->getId()) ? 'selected="selected"' : '';
			echo "<option value=\"{$group->getId()}\" $selected>$name</option>";
		}

		$selected = $this->title=='Other' ? 'selected="selected"' : '';
		echo "<option value=\"0\" $selected>Other</option>";
	?>
	</select>
</fieldset>
</form>

<?php include APPLICATION_HOME.'/blocks/html/locations/locationGroupMap.inc'; ?>