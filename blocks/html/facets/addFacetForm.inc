<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
?>
<h2>Add Facet</h2>
<form method="post" action="<?php echo $_SERVER['PHP_SELF']; ?>">
<fieldset><legend>Facet Info</legend>

	<table>
	<tr><td><label for="facet-name" class="required">Name</label></td>
		<td><input name="facet[name]" id="facet-name" /></td></tr>
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
	<tr><td colspan="2">
			<div><label>Description</label></div>
			<?php
				include APPLICATION_HOME.'/html/editors/fckeditor/FCKeditor.php';
				$FCKeditor = new FCKeditor("description");
				$FCKeditor->BasePath = BASE_URL.'/editors/fckeditor/';
				$FCKeditor->ToolbarSet = 'Custom';

				$FCKeditor->create();
			?>
	</td></tr>
	</table>

	<button type="submit" class="submit">Submit</button>
	<button type="button" class="cancel" onclick="document.location.href='<?php echo BASE_URL; ?>/facets';">Cancel</button>
</fieldset>
</form>
