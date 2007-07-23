<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param DocumentList $this->documents
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
			$title = View::escape($document->getTitle();
			echo "<li><a href=\"{$document->getURL()}\">$title</a></li>";
		}
		echo "</ul></div>";
	}
?>