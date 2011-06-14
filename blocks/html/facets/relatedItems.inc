<?php
/**
 * Creates the markup for the items tagged with this facet
 *
 * Facets can be used on both Documents and Locations, so be sure
 * to check the type on each item in the list
 *
 * @copyright 2007-2009 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Facet $this->facet
 */
#--------------------------------------------------------------------
# Remember the anchors we create, we're going to delay the rendering
# of this list, so we can display a table of contents on top
#--------------------------------------------------------------------
$displayedDocuments = array();
$displayedLocations = array();
$anchors = array();
$output = '';
foreach ($this->facet->getRelatedFacets() as $facet) {
	if ( ($facet->getId() != $this->facet->getId()) &&
		 ($this->facet->getFacetGroup()->isRelated($facet->getFacetGroup())) ) {

		$items = $facet->getItems();
		if (count($items)) {
			$name = View::escape($facet->getName());
			$anchor = WikiMarkup::wikify($facet->getName());
			$anchors[$anchor] = $name;
			$output.= "
			<h2><a id=\"$anchor\">$name</a></h2>
			<ul>
			";
			foreach($items as $item) {
				if ($item instanceof Document) {
					$displayedDocuments[$item->getId()] = $item;
					$title = $item->getFeature_title() ? $item->getFeature_title() : $item->getTitle();
				}
				elseif ($item instanceof Location) {
					$displayedLocations[$item->getId()] = $item;
					$title = $item->getName();
				}
				$title = View::escape($title);
				$output.= "<li><a href=\"{$item->getURL()}\">$title</a></li>\n";
			}
			$output.= "
			</ul>
			<a href=\"#top\">[Top]</a>
			";
		}
	}
}


#--------------------------------------------------------------------
# Table of Contents
# Go through all the anchors we've recorded and display them in
# a drop down list
#--------------------------------------------------------------------
$description = WikiMarkup::parse($this->facet->getDescription());
echo "<div>$description</div>";
if (count($displayedDocuments) || count($displayedLocations)) {
	echo "
	<div class=\"table-of-contents\">
		<form method=\"get\" action=\"$_SERVER[SCRIPT_NAME]\">
		<fieldset>
			<input type=\"hidden\" name=\"facet_id\" value=\"{$this->facet->getId()}\" />
			<label for=\"table-of-contents-anchor\">Table of Contents:</label>
			<select name=\"anchor\" id=\"table-of-contents-anchor\" onchange=\"document.location.href='#'+this.options[this.selectedIndex].value;\">
	";
			foreach($anchors as $anchor=>$name) {
				echo "<option value=\"$anchor\">$name</option>\n";
			}
	echo "
			</select>
		</fieldset>
		</form>
	</div>
	$output
	";
}
?>
<script type="text/javascript">
	function toggleSiblings(button) {
		var siblings = document.getElementById('siblings');
		if (siblings.style.display === 'none') {
			// Display the siblings
			siblings.style.display = '';
			button.className = 'less';
			button.firstChild.nodeValue = 'Less';
		}
		else {
			// Hide the siblings
			siblings.style.display = 'none';
			button.className = 'more';
			button.firstChild.nodeValue = 'More';
		}
	}
</script>
<?php
	$items = $this->facet->getItems();
	if (count($displayedDocuments) || count($displayedLocations)) {
		echo "
		<button type=\"button\" class=\"more\" onclick=\"toggleSiblings(this);\">More</button>
		<div id=\"siblings\" style=\"display:none;\">
		";
	}
	else {
		echo '<div id="siblings">';
	}

	echo '<ul>';
	foreach($items as $item) {
		if ($item instanceof Document) {
			if (!in_array($item->getId(),array_keys($displayedDocuments))) {
				$title = $item->getTitle();
			}
		}
		elseif ($item instanceof Location) {
			if (!in_array($item->getId(),array_keys($displayedLocations))) {
				$title = $item->getName();
			}
		}
		$title = View::escape($title);
		echo "<li><a href=\"{$item->getURL()}\">$title</a></li>";
	}
	echo '</ul></div>';
?>
