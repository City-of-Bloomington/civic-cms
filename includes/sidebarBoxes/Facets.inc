<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
	if (isset($this->document))
	{
		if (count($this->document->getRelatedDocuments()))
		{
			echo "<div><div class=\"titleBar\">Related</div><ul>";
			foreach($this->document->getRelatedDocuments() as $document)
			{
				echo "<li><a href=\"".BASE_URL."/documents/viewDocument.php?document_id={$document->getId()}\">{$document->getTitle()}</a></li>";
			}
			echo "</ul></div>";
		}
	}
?>