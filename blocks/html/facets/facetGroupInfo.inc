<?php
/**
 * @copyright 2009 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param FacetGroup $this->facetGroup
 */
?>
<div class="interfaceBox">
	<h2><?php
			$url = new URL(BASE_URL.'/facets/updateFacetGroup.php');
			if (isset($this->facetGroup)) {
				if (userHasRole(array('Administrator','Webmaster'))) {
					$url->parameters['facetGroup_id'] = $this->facetGroup->getId();
					echo "<a class=\"editSmall button\" href=\"$url\">Edit</a>";
				}
			}
			$title = View::escape($this->facetGroup->getName());
			echo "<a href=\"{$this->facetGroup->getURL()}\">$title</a>";
		?>
	</h2>
	<?php echo WikiMarkup::parse($this->facetGroup->getDescription()); ?>
</div>