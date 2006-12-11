<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
/*
	$this->document
	$this->FCKeditor
*/
	function printSectionOptions($section,$depth,$document)
	{
		$depthIndicator = str_repeat("-",$depth);
		$checked = $document->hasSection($section) ? "checked=\"checked\"" : "";
		echo "<li><label><input name=\"document[sections][{$section->getId()}]\" type=\"checkbox\" value=\"{$section->getId()}\" $checked />$section</label></li>";
		if ($section->hasChildren())
		{
			echo "<ul>";
			foreach($section->getChildren() as $child) { printSectionOptions($child,$depth+1,$document); }
			echo "</ul>";
		}
	}
?>
<form method="post" action="<?php echo $_SERVER['PHP_SELF']; ?>">
	<fieldset><legend>Document Info</legend>
		<input name="document_id" type="hidden" value="<?php echo $this->document->getId(); ?>" />
		<table>
		<tr><td><label for="document-title">Title</label></td>
			<td><input name="document[title]" id="document-title" value="<?php echo $this->document->getTitle(); ?>" /></td></tr>
		</table>
		<?php $this->FCKeditor->create(); ?>
	</fieldset>

	<fieldset><legend>Sections</legend>
		<?php
			$sections = new SectionList(array("parent_id"=>"null"));
			foreach($sections as $section)
			{
				printSectionOptions($section,0,$this->document);
			}
		?>
	</fieldset>

	<fieldset><legend>Facets</legend>
	<?php
		$facets = new FacetList();
		$facets->find();
		foreach($facets as $facet)
		{
			if ($this->document->hasFacet($facet)) { $checked = "checked=\"checked\""; } else { $checked = ""; }
			echo "<label><input type=\"checkbox\" name=\"document[facets][{$facet->getId()}]\" value=\"{$facet->getId()}\" $checked />{$facet->getName()}</label>";
		}
	?>
	</fieldset>

	<fieldset><legend>Submit</legend>
		<button type="submit" class="submit">Submit</button>
		<button type="button" class="cancel" onclick="document.location.href='<?php echo BASE_URL; ?>/documents/viewDocument.php?document_id=<?php echo $this->document->getId(); ?>';">Cancel</button>
	</fieldset>
</form>