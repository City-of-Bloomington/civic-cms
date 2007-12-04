<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Facet $this->facet (optional)
 */
?>
<div class="breadcrumbs">
<ul><li><a href="<?php echo BASE_URL; ?>">Home</a></li>
	<li><a href="<?php echo BASE_URL; ?>/facets">Facets</a></li>
	<?php
		if (isset($this->facet))
		{
			$name = View::escape($this->facet->getName());
			echo "<li>$name</li>";
		}
	?>
</ul>
</div>
