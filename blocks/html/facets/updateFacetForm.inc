<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham
 * @param Facet $this->facet
 */
?>
<h2>Update Facet</h2>
<form method="post" action="<?php echo $_SERVER['PHP_SELF']; ?>">
<fieldset><legend>Facet Info</legend>
	<input name="facet_id" type="hidden" value="<?php echo $this->facet->getId(); ?>" />

	<table>
	<tr><td><label for="facet-name" class="required">Name</label></td>
		<td><input name="facet[name]" id="facet-name" value="<?php echo View::escape($this->facet->getName()); ?>" /></td></tr>
	<tr><td colspan="2">
			<div><label for="facet-description">Description</label></div>
			<textarea name="facet[description]" id="facet-description" rows="3" cols="60"><?php echo View::escape($this->facet->getDescription()); ?></textarea>
	</td></tr>
	</table>
</fieldset>

<fieldset><legend class="required">Groups</legend>
	<p>You must choose at least one group for this facet.</p>
<?php
	$groups = new FacetGroupList();
	$groups->find();
	foreach($groups as $group)
	{
		$name = View::escape($group->getName());
		$checked = $group->hasFacet($this->facet) ? 'checked="checked"' : '';
		echo "
		<label>
			<input name=\"facet[facetGroups][{$group->getId()}]\" id=\"facet-facetGroups-{$group->getId()}\" type=\"checkbox\" value=\"{$group->getId()}\" $checked />
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
