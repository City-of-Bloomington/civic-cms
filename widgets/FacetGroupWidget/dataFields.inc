<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param SectionWidget $this->sectionWidget
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
		$facetGroup_id = $this->sectionWidget->getWidget()->getWidget()->facetGroup;

		$name = View::escape($group->getName());
		$selected = ($facetGroup_id==$group->getId()) ? 'selected="selected"' : '';
		echo "<option value=\"{$group->getId()}\" $selected>$name</option>";
	}
?>
</select>
</fieldset>
