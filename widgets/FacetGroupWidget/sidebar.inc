<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param FacetGroup $this->facetGroup
 */
?>
<div class="widget">
	<h1><?php echo View::escape($this->facetGroup->getName()); ?></h1>
	<ul>
	<?php
		foreach($this->facetGroup->getFacets() as $facet)
		{
			$name = View::escape($facet->getName());
			echo "<li><a href=\"".BASE_URL."/facets/viewFacet.php?facet_id={$facet->getId()}\">$name</a></li>\n";
		}
	?>
	</ul>
</div>
