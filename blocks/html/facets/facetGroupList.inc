<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param FacetGroupList $this->facetGroupList
 */
?>
<div class="interfaceBox">
	<div class="titleBar">
		<button type="button" class="addSmall" onclick="document.location.href='<?php echo BASE_URL; ?>/facets/addFacetGroup.php';">Add</button>
		Facet Groups
	</div>
	<ul><?php
			foreach($this->facetGroupList as $facetGroup)
			{
				echo "
				<li><button type=\"button\" class=\"editSmall\" onclick=\"document.location.href='".BASE_URL."/facets/updateFacetGroup.php?facetGroup_id={$facetGroup->getId()}';\">Edit</button>
					$facetGroup</li>
				";
			}
		?>
	</ul>
</div>
