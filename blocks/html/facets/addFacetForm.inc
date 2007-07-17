<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamN@bloomington.in.gov>
 */
?>
<h2>Add Facet</h2>
<form method="post" action="<?php echo $_SERVER['PHP_SELF']; ?>">
<fieldset><legend>Facet Info</legend>

	<table>
	<tr><td><label for="facet-name" class="required">Name</label></td>
		<td><input name="facet[name]" id="facet-name" /></td></tr>
	<tr><td colspan="2">
			<div><label for="facet-description">Description</label></div>
			<textarea name="facet[description]" id="facet-description" rows="3" cols="60"></textarea>
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
		echo "
		<label>
			<input name=\"facet[facetGroups][{$group->getId()}]\" id=\"facet-facetGroups-{$group->getId()}\" type=\"checkbox\" value=\"{$group->getId()}\" />
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
