<?php
/**
 * @copyright Copyright (C) 2007-2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param FacetGroupList $this->facetGroupList
 */
?>
<div class="interfaceBox">
	<h2>
		<a class="addSmall button" href="<?php echo BASE_URL; ?>/facets/addFacetGroup.php">Add</a>
		Facet Groups
	</h2>
	<ul><?php
			foreach($this->facetGroupList as $facetGroup)
			{
				echo "
				<li><a class=\"editSmall button\" href=\"".BASE_URL."/facets/updateFacetGroup.php?facetGroup_id={$facetGroup->getId()}\">Edit</a>
					$facetGroup</li>
				";
			}
		?>
	</ul>
</div>
