<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
/*
	$this->section
*/
	if (isset($this->section)) { $trails = $this->section->getAncestors(); }
	elseif (isset($this->document))
	{
		$trails = array();
		foreach($this->document->getSections() as $section)
		{
			$ancestors = $section->getAncestors();
			foreach($ancestors as $i=>$trail) { $ancestors[$i] = array_merge($ancestors[$i],array($section)); }
			$trails = array_merge($trails,$ancestors);
		}
	}


	if (isset($trails))
	{
		echo "<div id=\"breadcrumbs\">";
		foreach($trails as $trail)
		{
			echo "<ul>";
			foreach($trail as $section)
			{
				echo "<li><a href=\"".BASE_URL."/documents/viewDocument.php?document_id={$section->getDocument_id()}\">$section</a></li>";
				$currentSection = $section;
			}
			echo "</ul>";
		}
		echo "</div>";
	}
?>