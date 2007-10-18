<div class="breadcrumbs">
<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Document $this->document
 * @param array $_SESSION[vector] - The Navigation widget must initialize this
 */
	echo '<ul>';
	foreach($_SESSION['vector'] as $section)
	{
		$name = View::escape($section->getName());
		echo "<li><a href=\"{$section->getURL()}\">$name</a></li>";
	}
	echo '</ul>';
	$currentSection = $section;

?>
</div>
<?php
	if (count($this->document->getSections()) > 1)
	{
		echo "
		<div class=\"related-sections\">
		<ul><li>Related Sections</li>
		";
		foreach($this->document->getSections() as $section)
		{
			if ($section->getId() != $currentSection->getId())
			{
				$name = View::escape($section->getName());
				echo "<li><a href=\"{$section->getURL()}\">$name</a></li>";
			}
		}
		echo "
		</ul>
		</div>
		";
	}
?>
