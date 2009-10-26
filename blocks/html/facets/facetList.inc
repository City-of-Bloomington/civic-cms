<?php
/**
 * @copyright 2006-2009 City of Bloomington, Indiana
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param FacetList $this->facetList
 * @param FacetGroup $this->facetGroup (optional)  If provided, we'll list the documents as well,
										including a table of contents
 */
if ($this->facetGroup) {
	echo "
	<div class=\"table-of-contents\">
		<form method=\"get\" action=\"$_SERVER[SCRIPT_NAME]\">
		<fieldset>
			<input type=\"hidden\" name=\"facetGroup_id\" value=\"{$this->facetGroup->getId()}\" />
			<label for=\"table-of-contents-anchor\">Table of Contents:</label>
			<select name=\"anchor\" id=\"table-of-contents-anchor\"
				onchange=\"document.location.href='#'+this.options[this.selectedIndex].value;\">
	";
			foreach($this->facetList as $facet) {
				$name = View::escape($facet->getName());
				echo "<option value=\"facet_{$facet->getId()}\">$name</option>\n";
			}
	echo "
			</select>
		</fieldset>
		</form>
	</div>
	";
}
else {
	echo '<ul>';
}
foreach ($this->facetList as $facet) {
	$tag = $this->facetGroup ? 'h4' : 'li';
	echo "
	<$tag id=\"facet_{$facet->getId()}\">
	";
	if (userHasRole(array('Administrator','Webmaster'))) {
		echo "
		<a class=\"editSmall button\" href=\"".BASE_URL."/facets/updateFacet.php?facet_id={$facet->getId()}\">
			Edit
		</a>
		<button type=\"button\" class=\"deleteSmall\" onclick=\"FRAMEWORK.deleteConfirmation('".BASE_URL."/facets/deleteFacet.php?facet_id={$facet->getId()}');\">
			Delete
		</button>
		";
	}

	$name = View::escape($facet->getName());
	echo "
		<a href=\"{$facet->getURL()}\">$name</a>
	</$tag>
	";

	if ($this->facetGroup) {
		$block = new Block('facets/facetDocuments.inc',array('facet'=>$facet));
		echo $block->render();
		echo "<a href=\"#top\">[Top]</a>";
	}
}
if (!$this->facetGroup) {
	echo '</ul>';
}