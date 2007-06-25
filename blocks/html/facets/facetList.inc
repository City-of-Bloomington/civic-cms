<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param FacetList $this->facetList
 */
?>
<div class="interfaceBox">
	<div class="titleBar">
		<?php if (userHasRole('Webmaster')) { echo "<button type=\"button\" class=\"addSmall\" onclick=\"document.location.href='".BASE_URL."/facets/addFacet.php';\">Add</button>"; } ?>
		Facets
	</div>
	<ul><?php
			foreach($this->facetList as $facet)
			{
				echo '<li>';
				if (userHasRole('Webmaster')) { echo "<button type=\"button\" class=\"editSmall\" onclick=\"document.location.href='".BASE_URL."/facets/updateFacet.php?facet_id={$facet->getId()}';\">Edit</button>"; }
				echo View::escape($facet->getName()).'</li>';
			}
		?>
	</ul>
</div>
