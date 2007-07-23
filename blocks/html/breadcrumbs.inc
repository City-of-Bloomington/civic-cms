<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Document $this->document
 */
	$trails = array();
	foreach($this->document->getSections() as $section)
	{
		$ancestors = $section->getAncestors();
		foreach($ancestors as $i=>$trail) { $ancestors[$i] = array_merge($ancestors[$i],array($section)); }
		$trails = array_merge($trails,$ancestors);
	}


	if (isset($trails))
	{
		echo "<div id=\"breadcrumbs\">";
		foreach($trails as $trail)
		{
			echo "<ul>";
			foreach($trail as $section)
			{
				$name = View::escape($section->getName());
				echo "<li><a href=\"{$section->getDocument()->getURL()}\"$name</a></li>";
				$currentSection = $section;
			}
			echo "</ul>";
		}
		echo "</div>";
	}
?>