<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
/*
	$this->document
*/
	foreach($this->document->getSections() as $section)
	{
		echo "<div class=\"interfaceBox\"><div class=\"titleBar\">$section</div><ul>";
		foreach($section->getDocuments() as $document)
		{
			if ($document->getId() != $this->document->getId())
			{
				echo "<li><a href=\"".BASE_URL."/documents/viewDocument.php?document_id={$document->getId()}\">";
				echo View::sanitizeString($document->getTitle());
				echo "</a></li>";
			}
		}
		foreach($section->getChildren() as $child)
		{
			echo "<li><a href=\"".BASE_URL."/documents/viewDocument.php?document_id={$child->getDocument_id()}\">";
			echo View::sanitizeString($child->getName());
			echo "<ul>";
			foreach($child->getDocuments() as $document)
			{
				if ($document->getId() != $child->getDocument_id())
				{
					echo "<li><a href=\"".BASE_URL."/documents/viewDocument.php?document_id={$document->getId()}\">";
					echo View::sanitizeString($document->getTitle());
					echo "</a></li>";
				}
			}
			echo "</ul>";
			echo "</a></li>";
		}
		echo "</ul></div>";
	}
?>