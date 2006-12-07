<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
	if (isset($this->section)) { $facets = $this->section->getFacets(); }
	if (isset($this->document)) { $facets = $this->document->getFacets(); }

	if (isset($facets) && count($facets))
	{
		echo "<div><div class=\"titleBar\">Related</div><ul>";
		foreach($facets as $facet)
		{
			echo "<li>$facet";
			if (count($facet->getDocuments()))
			{
				echo "<ul>";
				foreach($facet->getDocuments() as $document)
				{
					if (isset($this->document) && $this->document->getId()!=$document->getId())
					{
						echo "<li><a href=\"".BASE_URL."/documents/viewDocument.php?document_id={$document->getId()}\">{$document->getTitle()}</a></li>";
					}
				}
				echo "</ul>";
			}
			echo "</li>";
		}
		echo "</ul></div>";
	}
?>