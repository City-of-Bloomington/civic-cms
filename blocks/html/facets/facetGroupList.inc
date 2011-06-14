<?php
/**
 * @copyright 2007-2009 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param FacetGroupList $this->facetGroupList
 * @param boolean $this->displayDocuments
 */
?>
<div class="interfaceBox">
	<h2><?php
			if (userHasRole(array('Administrator','Webmaster'))) {
				echo "
				<a class=\"addSmall button\" href=\"".BASE_URL."/facets/addFacetGroup.php\">
					Add
				</a>
				";
			}
		?>
		Facet Groups
	</h2>
	<?php
		foreach($this->facetGroupList as $facetGroup) {
			$name = View::escape($facetGroup->getName());
			$editButton = '';
			if (userHasRole(array('Administrator','Webmaster'))) {
				$editButton = "
				<a class=\"editSmall button\" href=\"".BASE_URL."/facets/updateFacetGroup.php?facetGroup_id={$facetGroup->getId()}\">
					Edit
				</a>
				";
			}
			echo "<h3>$editButton<a href=\"{$facetGroup->getURL()}\">$name</a></h3>";
			$block = new Block('facets/facetList.inc',array('facetList'=>$facetGroup->getFacets()));
			echo $block->render();
		}
	?>
</div>
