<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
?>
<h1>Add Facet Group</h1>
<form method="post" action="<?php echo $_SERVER['PHP_SELF']; ?>">
<fieldset><legend>Facet Group Info</legend>

	<table>
	<tr><td><label for="facetGroup-name" class="required">Name</label></td>
		<td><input name="facetGroup[name]" id="facetGroup-name" /></td></tr>
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

<fieldset><legend>Submit</legend>
	<button type="submit" class="submit">Submit</button>
	<button type="button" class="cancel" onclick="document.location.href='<?php echo BASE_URL; ?>/facets';">Cancel</button>
</fieldset>
</form>
