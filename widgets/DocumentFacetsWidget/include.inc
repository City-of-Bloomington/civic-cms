<?php
/**
 * @copyright 2009 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Document $this->document
 */
foreach($this->document->getFacetGroups() as $facetGroup) {
	$name = View::escape($facetGroup->getName());
	$class = WikiMarkup::wikify($facetGroup->getName());
	echo "
	<div class=\"widget $class\">
		<h1>$name</h1>
		<ul>
	";
			$facets = $this->document->getFacets(array('facetGroup_id'=>$facetGroup->getId()));
			foreach ($facets as $facet) {
				$name = View::escape($facet->getName());
				$class = WikiMarkup::wikify($facet->getName());
				echo "
				<li class=\"$class\">
					<a href=\"".BASE_URL."/facets/viewFacet.php?facet_id={$facet->getId()}\">
						$name
					</a>
				</li>
				";
			}
	echo "
		</ul>
	</div>
	";
}
