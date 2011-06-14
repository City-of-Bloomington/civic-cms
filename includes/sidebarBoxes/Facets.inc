<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Document $this->document
 */
	if (isset($this->document))
	{
		if (count($this->document->getRelatedDocuments()))
		{
			echo "<div><h1>Related</h1><ul>";
			foreach($this->document->getRelatedDocuments() as $document)
			{
				$title = View::escape($document->getTitle());
				echo "<li><a href=\"{$document->getURL()}\">$title</a></li>";
			}
			echo "</ul></div>";
		}
	}
?>