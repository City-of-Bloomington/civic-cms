<?php
/**
 * @copyright Copyright (C) 2007-2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param FacetGroup $this->facetGroup
 */
$name = View::escape($this->facetGroup->getName());
$class = WikiMarkup::wikify($this->facetGroup->getName());
echo "
<div class=\"widget $class\">
	<h1>$name</h1>
	<ul>
";
		foreach($this->facetGroup->getFacets() as $facet)
		{
			$name = View::escape($facet->getName());
			$class = WikiMarkup::wikify($facet->getName());
			echo "\t\t<li class=\"$class\"><a href=\"".BASE_URL."/facets/viewFacet.php?facet_id={$facet->getId()}\">$name</a></li>\n";
		}
echo "
	</ul>
</div>
";