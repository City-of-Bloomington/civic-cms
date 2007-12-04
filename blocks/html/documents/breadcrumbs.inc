<div class="breadcrumbs">
<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Document $this->document
 * @param Section $this->section
 * @param array $this->currentAncestors
 * @param array $this->relatedAncestors
 */
	$currentSection = View::escape($this->section);

	echo '<ul>';
	foreach($this->currentAncestors as $section)
	{
		$name = View::escape($section);
		echo "<li><a href=\"{$section->getURL()}\">$name</a></li>";
	}
	echo "<li>$currentSection</li>";
	echo '</ul>';

	foreach($this->relatedAncestors as $vector)
	{
		echo '<ul><li>Related Sections: </li>';
		foreach($vector as $section)
		{
			$name = View::escape($section);
			echo "<li><a href=\"{$section->getURL()}\">$name</a></li>";
		}
		echo "<li>$currentSection</li>";
		echo '</ul>';
	}
?>
</div>
