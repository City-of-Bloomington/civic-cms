<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Document $this->document
 * @param array $this->currentAncestors
 */
echo "
<div id=\"pageTitle\">
	<div class=\"breadcrumbs\">
		<ul>
";
		$f = count($this->currentAncestors) - 1;
		$c = 0;
		foreach($this->currentAncestors as $section)
		{
			$c++;

			$name = View::escape($section);
			if ($c > $f) { echo "\t\t<li>$name</li>\n"; }
			else { echo "\t\t<li><a href=\"{$section->getURL()}\">$name</a></li>\n"; }

			$currentSection = $section->getId();
		}
echo "
		</ul>
	</div>
";

# List all the parents of the curent document as a related section
# Don't try and show the full ancestral line of each of these
if (count($this->document->getSections())>1)
{
	$relatedSections = array();
	foreach($this->document->getSections() as $section)
	{
		if ($section->getId() != $currentSection)
		{
			$name = View::escape($section);
			$relatedSections[] = "<a href=\"{$section->getURL()}\">$name</a>";
		}
	}
	$relatedSections = implode(', ',$relatedSections);

	echo "
	<div class=\"related-sections\">
		Related Sections:
		$relatedSections
	</div>
	";
}

$title = View::escape($this->document->getTitle());
echo "
	<h1>$title</h1>
</div>
";
