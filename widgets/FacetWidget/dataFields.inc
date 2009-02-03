<?php
/**
 * @copyright 2007 City of Bloomington, Indiana
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Widget $this->widget
 */
?>
<fieldset><legend>Choose a Facet Group</legend>
	<label for="facetGroup_id">Facet Groups</label>
	<select name="facetGroup_id" id="facetGroup_id">
	<?php
		$facetGroup_id = $this->widget->facetGroup->getId();

		$list = new FacetGroupList();
		$list->find();
		foreach ($list as $group) {
			$name = View::escape($group->getName());
			$selected = ($facetGroup_id==$group->getId()) ? 'selected="selected"' : '';
			echo "<option value=\"{$group->getId()}\" $selected>$name</option>";
		}
	?>
	</select>
</fieldset>
