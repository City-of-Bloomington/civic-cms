<?php
/**
 * @copyright 2006-2009 City of Bloomington, Indiana
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param FacetList $this->facetList
 * @param string $this->title
 * @param FacetGroup $this->facetGroup (optional)
 */
if (isset($this->facetGroup)) {
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
?>
<div class="interfaceBox">
	<h2><?php
			$url = new URL(BASE_URL.'/facets/updateFacetGroup.php');
			if (isset($this->facetGroup)) {
				if (userHasRole(array('Administrator','Webmaster'))) {
					$url->parameters['facetGroup_id'] = $this->facetGroup->getId();
					echo "<a class=\"editSmall button\" href=\"$url\">Add</a>";
				}
			}
			$title = View::escape($this->title);
			echo "<a href=\"{$this->facetGroup->getURL()}\">$title</a>";
		?>
	</h2>
	<?php
		foreach($this->facetList as $facet) {
			echo "
			<h3 id=\"facet_{$facet->getId()}\">
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
			</h3>
			";

			$block = new Block('facets/facetDocuments.inc',array('facet'=>$facet));
			echo $block->render();

			echo "<a href=\"#top\">[Top]</a>";
		}
	?>
</div>
