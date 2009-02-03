<?php
/**
 * @copyright 2007-2009 City of Bloomington, Indiana
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param FacetGroupList $this->facetGroupList
 */
echo "
<div class=\"widget\">
	<h1>Facet Groups</h1>
	<ul>
";
		foreach ($this->facetGroupList as $facetGroup) {
			$name = View::escape($facetGroup->getName());
			echo "<li><a href=\"{$facetGroup->getURL()}\">$name</a></li>";
		}
echo "
	</ul>
</div>
";
