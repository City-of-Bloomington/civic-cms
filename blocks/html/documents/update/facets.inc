<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Document $this->document
 */
?>
<form id="documentForm" method="post" action="<?php echo $_SERVER['PHP_SELF']; ?>">
	<fieldset><legend>Next</legend>
		<p>Move on to the next tab.  The document will not be saved to the database until you click the "Save" button.</p>
		<input type="hidden" name="tab" id="tab" value="info" />
		<input type="hidden" name="action" id="action" value="next" />
		<button type="submit" class="next">Next</button>
		<button type="cancel" class="cancel" onclick="self.close();">Cancel</button>
		<button type="button" class="save" onclick="FRAMEWORK.processTabbedForm('documentForm','facets','save');">Save</button>
	</fieldset>
	<?php
		$groups = new FacetGroupList();
		$groups->find();
		foreach($groups as $group)
		{
			$name = View::escape($group->getName());
			echo "<fieldset><legend>$name</legend>";

			foreach($group->getFacets() as $facet)
			{
				$facetName = View::escape($facet->getName());
				if ($this->document->hasFacet($facet)) { $checked = "checked=\"checked\""; } else { $checked = ""; }
				echo "<label><input type=\"checkbox\" name=\"document[facets][{$facet->getId()}]\" value=\"{$facet->getId()}\" $checked />$facetName</label>";
			}
			echo "</fieldset>";
		}
	?>

	<fieldset><legend>Next</legend>
		<p>Move on to the next tab.  The document will not be saved to the database until you click the "Save" button.</p>
		<button type="submit" class="next">Next</button>
		<button type="cancel" class="cancel" onclick="self.close();">Cancel</button>
		<button type="button" class="save" onclick="FRAMEWORK.processTabbedForm('documentForm','facets','save');">Save</button>
	</fieldset>
</form>
