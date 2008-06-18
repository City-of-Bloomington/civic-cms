<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
?>
<h1>Add Facet</h1>
<form method="post" action="<?php echo $_SERVER['SCRIPT_NAME']; ?>">
<fieldset><legend>Facet Info</legend>

	<table>
	<tr><td><label for="facet-name" class="required">Name</label></td>
		<td><input name="facet[name]" id="facet-name" size="60" /></td></tr>
	<tr><td><label for="facet-facetGroup_id" class="required">Group</label></td>
		<td><select name="facet[facetGroup_id]" id="facet-facetGroup_id">
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
		</td>
	</tr>
	<tr><td><label for="facet-ordering">Ordering</label></td>
		<td><input name="facet[ordering]" id="facet-ordering" size="2" maxlength="2" /></td>
	</tr>
	<tr><td colspan="2">
			<div><label for="description">Description</label></div>
			<?php
				$content = '';
				$content_field_name = 'description';
				include APPLICATION_HOME.'/includes/editors/'.EDITOR.'/editor_init.inc';
			?>
	</td></tr>
	</table>

	<button type="submit" class="submit">Submit</button>
	<a class="cancel" href="<?php echo BASE_URL; ?>/facets">Cancel</a>
</fieldset>
</form>
