<?php
/**
 * @copyright 2014 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param FacetGroup $this->facetGroup
 * @param Facet $this->facet
 */
$url = new URL($_SERVER['SERVER_NAME'].$_SERVER['REQUEST_URI']);

echo "
<div class=\"tabBar\">
	<ul>
";
	foreach ($this->facetGroup->getFacets() as $facet) {
		$class = ($this->facet && $this->facet->getId()==$facet->getId())
			? 'class="current"'
			: '';
		$url->facet_id = $facet->getId();
		$name = View::escape($facet);
		echo "<li $class><a href=\"$url\">$name</a></li>";
	}
echo "
	</ul>
</div>
";
