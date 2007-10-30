<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Document $this->document
 */
	foreach ($this->document->getSections() as $section)
	{
		if ($section->hasChildren()) { renderNavigation($section); }
		else
		{
			# For sections without children, show the navigation of each parent section
			foreach($section->getParents() as $section) { renderNavigation($section); }
		}
	}

	function renderNavigation($section)
	{
		$name = View::escape($section->getName());
		echo "
		<div class=\"widget\"><h1>$name</h1>
		<ul>
		";
		foreach($section->getChildren() as $child)
		{
			$title = View::escape($chid->getTitle());
			echo "<li><a href=\"{$document->getURL()}\">$title</a></li>\n";
		}
		echo "
		</ul>
		</div>
		";
	}
?>
