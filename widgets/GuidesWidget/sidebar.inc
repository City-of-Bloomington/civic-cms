<div><div class="titleBar">Guides</div>
<ul><?php
		$guides = new FacetGroup('Guides');
		foreach($guides->getFacets() as $facet)
		{
			$name = View::escape($facet->getName());
			echo "<li><a href=\"".BASE_URL."/facets/viewFacet.php?facet_id={$facet->getId()}\">$name</a></li>\n";
		}
	?>
</ul>
</div>
