<?php
/**
 * @copyright Copyright (C) 2007-2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Facet $this->facet (optional)
 */
$title = isset($this->facet) ? View::escape($this->facet->getName()) : 'Facets';
?>
<div id="pageTitle">
	<div class="breadcrumbs">
	<ul><li><a href="<?php echo BASE_URL; ?>">Home</a></li>
		<li><a href="<?php echo BASE_URL; ?>/facets">Facets</a></li>
		<?php
			if (isset($this->facet))
			{
				echo "<li><a href=\"{$this->facet->getURL()}\">$title</a></li>";
			}
		?>
	</ul>
	</div>
	<h1>
	<?php
		if (userHasRole(array('Administrator','Webmaster')))
		{
			echo "<a class=\"addSmall button\" href=\"".BASE_URL."/facets/addFacet.php\">Add</a>";
		}
		echo $title;
	?>
	</h1>
</div>
