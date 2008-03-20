<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param object $this->documentType
 */
?>
<h1>Edit <?php echo $this->documentType; ?></h1>
<form method="post" action="<?php echo $_SERVER['PHP_SELF']; ?>">
<fieldset><legend>Document Type</legend>
	<input name="documentType_id" type="hidden" value="<?php echo $this->documentType->getId(); ?>" />

	<table>
	<tr><td><label for="documentType-type">Type</label></td>
		<td><input name="documentType[type]" id="documentType-type" size="60" value="<?php echo View::escape($this->documentType->getType()); ?>" /></td></tr>
	<tr><td><label for="documentType-media_id">Icon</label></td>
		<td><button type="button" class="browse" onclick="window.open('<?php echo BASE_URL; ?>/media/imageBrowser.php');">Choose Media</button>
			<button type="button" class="deleteSmall" onclick="removeIcon();">Delete</button>
			<input name="documentType[media_id]" id="documentType-media_id" type="hidden" value="<?php echo $this->documentType->getMedia_id(); ?>" />
			<span id="icon">
			<?php
				if ($this->documentType->getMedia_id())
				{
					echo "<img src=\"".BASE_URL."/media/media.php?media_id={$this->documentType->getMedia_id()};size=thumbnail\" />";
				}
			?>
			</span>
			<script type="text/javascript">
			var icon = document.getElementById('icon');
			function handleSelection(media_id)
			{
				var BASE_URL = '<?php echo BASE_URL; ?>';
				document.getElementById('documentType-media_id').value = media_id;

				// Update the icon
				while(icon.hasChildNodes()) { icon.removeChild(icon.firstChild); }
				var img = document.createElement('img');
				img.src = BASE_URL+'/media/media.php?size=thumbnail;media_id='+media_id;
				icon.appendChild(img);
			}
			function removeIcon()
			{
				while(icon.hasChildNodes()) { icon.removeChild(icon.firstChild); }
				document.getElementById('documentType-media_id').value = '';
			}
			</script>
		</td>
	</tr>
	<tr><td colspan="2">
		<label for="documentType-template">Template</label>
		<textarea name="documentType[template]" id="documentType-template" rows="20" cols="60"><?php echo $this->documentType->getTemplate(); ?></textarea>
		</td>
	</tr>
	</table>
</fieldset>

<fieldset><legend>List Display Information</legend>
<p>Choose the information you want to display when documents of this type
are displayed in a list.</p>
<div>
<?php
	foreach(Document::getDisplayableFields() as $field=>$name)
	{
		$checked = in_array($field,$this->documentType->getDocumentInfoFields()) ? 'checked="checked"' : '';
		echo "
		<label>
			<input name=\"documentType[documentInfoFields][]\" type=\"checkbox\" value=\"$field\" $checked />
			$name
		</label>
		";
	}
?>
</div>
</fieldset>

<fieldset><legend>Display Options</legend>
	<table>
	<tr><td><label for="documentType-ordering-field">Ordering</label></td>
		<td><select name="documentType[ordering][field]" id="documentType-ordering-field">
			<?php
				foreach(Document::getDisplayableFields() as $field=>$name)
				{
					$selected = preg_match("/$field/",$this->documentType->getOrdering()) ? 'selected="selected"' : '';
					echo "<option value=\"$field\" $selected>$name</option>\n";
				}
			?>
			</select>
			<select name="documentType[ordering][direction]" id="documentType-ordering-direction">
				<option value="asc" <?php if(preg_match('/asc/',$this->documentType->getOrdering())) echo 'selected="selected"'; ?>>Ascending</option>
				<option value="desc"<?php if(preg_match('/desc/',$this->documentType->getOrdering())) echo 'selected="selected"'; ?>>Descending</option>
			</select>
		</td>
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
	<a class="cancel" href="<?php echo BASE_URL; ?>/documentTypes">Cancel</a>
</fieldset>
</form>
