<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
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
		echo "<option value=\"{$group->getId()}\">$name</option>";
	}
?>
</select>
</fieldset>
