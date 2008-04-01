<?php
/**
 * @copyright Copyright (C) 2006-2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param FacetList $this->facetList
 * @param string $this->title
 * @param FacetGroup $this->facetGroup (optional)
 */
?>
<div class="interfaceBox">
	<h2>
		<?php
			$url = new URL(BASE_URL.'/facets/updateFacetGroup.php');
			if (isset($this->facetGroup))
			{
				if (userHasRole(array('Administrator','Webmaster')))
				{
					$url->parameters['facetGroup_id'] = $this->facetGroup->getId();
					echo "<a class=\"editSmall button\" href=\"$url\">Add</a>";
				}
			}
			echo View::escape($this->title);
		?>
	</h2>
	<ul><?php
			foreach($this->facetList as $facet)
			{
				echo '<li>';
				if (userHasRole(array('Administrator','Webmaster')))
				{
					echo "
					<a class=\"editSmall button\" href=\"".BASE_URL."/facets/updateFacet.php?facet_id={$facet->getId()}\">Edit</a>
					<button type=\"button\" class=\"deleteSmall\" onclick=\"FRAMEWORK.deleteConfirmation('".BASE_URL."/facets/deleteFacet.php?facet_id={$facet->getId()}');\">Delete</button>
					";
				}

				$name = View::escape($facet->getName());
				echo "<a href=\"".BASE_URL."/facets/viewFacet.php?facet_id={$facet->getId()}\">$name</a></li>";
			}
		?>
	</ul>
</div>
