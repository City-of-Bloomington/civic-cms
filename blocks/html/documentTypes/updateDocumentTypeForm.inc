<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param object $this->documentType
 */
?>
<h2>Edit <?php echo $this->documentType; ?></h2>
<form method="post" action="<?php echo $_SERVER['PHP_SELF']; ?>">
<fieldset><legend>Document Type</legend>
	<input name="documentType_id" type="hidden" value="<?php echo $this->documentType->getId(); ?>" />

	<table>
	<tr><td><label for="documentType-type">Type</label></td>
		<td><input name="documentType[type]" id="documentType-type" value="<?php echo View::escape($this->documentType->getType()); ?>" /></td></tr>
	<tr><td colspan="2">
		<label for="documentType-template">Template</label>
		<textarea name="documentType[template]" id="documentType-template" rows="20" cols="60"><?php echo $this->documentType->getTemplate(); ?></textarea>
		</td>
	</tr>
	</table>
</fieldset>

<fieldset><legend>Display Options</legend>
	<table>
	<tr><td><label for="documentType-ordering">Ordering</label></td>
		<td><input name="documentType[ordering]" id="documentType-ordering" value="<?php echo View::escape($this->documentType->getOrdering()); ?>" /></td>
		<td><p>This ordering field controls how documents of this type are sorted when they are displayed as a list.
				For instance in the 'Information in $section' box.</p>
		</td>
	</tr>
	<tr><td><label for="documentType-defaultFacetGroup_id">Default Facet Group</label></td>
		<td><select name="documentType[defaultFacetGroup_id]"><option></option>
			<?php
				$list = new FacetGroupList();
				$list->find();
				foreach($list as $group)
				{
					$name = View::escape($group->getName());
					$selected = ($group->getId() == $this->documentType->getDefaultFacetGroup_id()) ? 'selected="selected"' : '';
					echo "<option value=\"{$group->getId()}\" $selected>$name</option>";
				}
			?>
			</select>
		</td>
		<td><p>Choose the Facet Group you want to be selected by default when the list of all documents of this type is displayed.</p></td>
	</tr>
	</table>
</fieldset>

<fieldset><legend>Submit</legend>
	<button type="submit" class="submit">Save</button>
	<button type="button" class="cancel" onclick="document.location.href='<?php echo BASE_URL; ?>/documentTypes';">Cancel</button>
</fieldset>
</form>
