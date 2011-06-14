<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
?>
<h1>Add Facet Group</h1>
<form method="post" action="<?php echo $_SERVER['SCRIPT_NAME']; ?>">
<fieldset><legend>Facet Group Info</legend>

	<table>
	<tr><td><label for="facetGroup-name" class="required">Name</label></td>
		<td><input name="facetGroup[name]" id="facetGroup-name" size="60" /></td></tr>
	</table>
</fieldset>

<fieldset><legend>Related Groups</legend>
<p>When showing this facet, the system will also display any related documents of facets from the the groups you select here.</p>
<?php
	$list = new FacetGroupList();
	$list->find();
	foreach($list as $group)
	{
		$name = View::escape($group->getName());
		echo "
		<label>
			<input name=\"facetGroup[relatedGroups][{$group->getId()}]\" id=\"facetGroup-relatedGroups-{$group->getId()}\" value=\"{$group->getId()}\" type=\"checkbox\" />
			$name
		</label>
		";
	}
?>
</fieldset>

<fieldset><legend>Departments</legend>
	<p>Choose the departments that are allowed to assign the Facets from inside this group to Documents.</p>
	<table>
	<?php
		$list = new DepartmentList();
		$list->find();
		foreach($list as $department)
		{
			$name = View::escape($department->getName());
			$checked = ($department->getId()==$_SESSION['USER']->getDepartment_id()) ? 'checked="checked"' : '';
			echo "
			<tr><td><input type=\"checkbox\" name=\"facetGroup[departments][{$department->getId()}]\" id=\"facetGroup-departments-{$department->getId()}\" value=\"{$department->getId()}\" $checked /></td>
				<td><label for=\"facetGroup-departments-{$department->getId()}\">$name</label></td></tr>
			";
		}
	?>
	</table>
</fieldset>

<fieldset><legend>Submit</legend>
	<button type="submit" class="submit">Submit</button>
	<a class="cancel" href="<?php echo BASE_URL; ?>/facets">Cancel</a>
</fieldset>
</form>
