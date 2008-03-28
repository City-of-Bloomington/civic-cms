<div class="interfaceBox">
	<h2><a href="<?php echo BASE_URL; ?>/facets">Facets</a></h2>
<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
	include_once APPLICATION_HOME.'/includes/js/tree.inc';

	$list = new FacetGroupList();
	$list->find();
	echo '<ul class="mktree">';
	foreach($list as $group)
	{
		$name = View::escape($group->getName());
		echo "<li><a href=\"\">$name</a>";
		if (count($group->getFacets()))
		{
			echo '<ul>';
			foreach($group->getFacets() as $facet)
			{
				$name = View::escape($facet->getName());
				echo "<li><a href=\"{$facet->getURL()}\">$name</a></li>";
			}
			echo '</ul>';
		}
		echo '</li>';
	}
	echo '</ul>';
?>
</div>
