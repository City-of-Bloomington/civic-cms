<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param string $data
 * Scripts that want to include these fields need to give this script
 * a current copy of the data, so we can render the form appropriately
 */
?>
<fieldset><legend>Choose a Facet Group</legend>
<label for="facetGroup_id">Facet Groups</label>
<select name="facetGroup_id" id="facetGroup_id">
<?php
	$list = new FacetGroupList();
	$list->find();
	foreach($list as $group)
	{
		$name = View::escape($group->getName());
		$selected = (isset($data) && $data==$group->getId()) ? 'selected="selected"' : '';
		echo "<option value=\"{$group->getId()}\" $selected>$name</option>";
	}
?>
</select>
</fieldset>
