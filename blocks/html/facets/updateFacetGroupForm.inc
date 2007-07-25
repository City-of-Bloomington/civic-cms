<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param FacetGroup $this->facetGroup
 */
?>
<h1>Update Facet Group</h1>
<form method="post" action="<?php echo $_SERVER['PHP_SELF']; ?>">
<fieldset><legend>Facet Group Info</legend>
	<input name="facetGroup_id" type="hidden" value="<?php echo $this->facetGroup->getId(); ?>" />

	<table>
	<tr><td><label for="facetGroup-name" class="required">Name</label></td>
		<td><input name="facetGroup[name]" id="facetGroup-name" value="<?php echo $this->facetGroup->getName(); ?>" /></td></tr>
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
		$checked = in_array($group->getId(),array_keys($this->facetGroup->getRelatedGroups())) ? 'checked="checked"' : '';
		echo "
		<label>
			<input name=\"facetGroup[relatedGroups][{$group->getId()}]\" id=\"facetGroup-relatedGroups-{$group->getId()}\" value=\"{$group->getId()}\" type=\"checkbox\" $checked />
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
