<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
/*
	$this->documents
*/
	if (count($this->documents))
	{
		echo "
		<div class=\"widget\">
			<div class=\"titleBar\">Whats New</div>
			<ul>
		";
		foreach($this->documents as $document)
		{
			echo "
			<li><a href=\"".BASE_URL."/documents/viewDocument.php?document_id={$document->getId()}\">{$document->getTitle()}</a></li>
			";
		}
		echo "</ul></div>";
	}
?>