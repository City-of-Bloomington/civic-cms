<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param FacetList $this->facetList
 * @param string $this->title
 * @param FacetGroup $this->facetGroup (optional)
 */
?>
<div class="interfaceBox">
	<h1>
		<?php
			$url = new URL(BASE_URL.'/facets/updateFacetGroup.php');
			if (isset($this->facetGroup))
			{
				if (userHasRole(array('Administrator','Webmaster')))
				{
					$url->parameters['facetGroup_id'] = $this->facetGroup->getId();
					echo "<button type=\"button\" class=\"editSmall\" onclick=\"document.location.href='$url';\">Add</button>";
				}
			}
			echo View::escape($this->title);
		?>
	</h1>
	<ul><?php
			foreach($this->facetList as $facet)
			{
				echo '<li>';
				if (userHasRole(array('Administrator','Webmaster')))
				{
					echo "
					<button type=\"button\" class=\"editSmall\" onclick=\"document.location.href='".BASE_URL."/facets/updateFacet.php?facet_id={$facet->getId()}';\">Edit</button>
					<button type=\"button\" class=\"deleteSmall\" onclick=\"FRAMEWORK.deleteConfirmation('".BASE_URL."/facets/deleteFacet.php?facet_id={$facet->getId()}');\">Delete</button>
					";
				}

				$name = View::escape($facet->getName());
				echo "<a href=\"".BASE_URL."/facets/viewFacet.php?facet_id={$facet->getId()}\">$name</a></li>";
			}
		?>
	</ul>
</div>
