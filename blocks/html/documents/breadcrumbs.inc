<div class="breadcrumbs">
<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Document $this->document
 * @param array $this->currentAncestors
 * @param array $this->relatedAncestors
 */
	echo '<ul>';
	foreach($this->currentAncestors as $section)
	{
		$name = View::escape($section);
		echo "<li><a href=\"{$section->getURL()}\">$name</a></li>";
	}
	echo '</ul>';

	foreach($this->relatedAncestors as $vector)
	{
		echo '<ul><li>Related Sections: </li>';
		foreach($vector as $section)
		{
			$name = View::escape($section);
			echo "<li><a href=\"{$section->getURL()}\">$name</a></li>";
		}
		echo '</ul>';
	}
?>
</div>
