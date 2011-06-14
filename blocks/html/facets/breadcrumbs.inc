<?php
/**
 * @copyright 2007-2009 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Facet $this->facet (optional)
 * @param FacetGroup $this->facetGroup (optional)
 */
$title = 'Facets';
if (isset($this->facet)) {
	$title = View::escape($this->facet->getName());
}
elseif (isset($this->facetGroup)) {
	$title = View::escape($this->facetGroup->getName());
}
?>
<div id="pageTitle">
	<div class="breadcrumbs">
		<ul><li><a href="<?php echo BASE_URL; ?>">Home</a></li>
			<li><a href="<?php echo BASE_URL; ?>/facets">Facets</a></li>
			<?php
				if (isset($this->facet)) {
					echo "<li><a href=\"{$this->facet->getURL()}\">$title</a></li>";
				}
			?>
		</ul>
	</div>
	<h1>
	<?php
		if (userHasRole(array('Administrator','Webmaster'))) {
			echo "<a class=\"addSmall button\" href=\"".BASE_URL."/facets/addFacet.php\">Add</a>";
		}
		echo $title;
	?>
	</h1>
</div>
