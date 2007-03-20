<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Document $this->document
 */
	foreach ($this->document->getSections() as $section)
	{
		echo "
		<div><div class=\"titleBar\">$section</div>
		<ul>
		";
		foreach($section->getChildren() as $child)
		{
			echo "
			<li><a href=\"".BASE_URL."/documents/viewDocument.php?document_id={$child->getDocument_id()}\">$child</a></li>
			";
		}
		echo "
		</ul>
		</div>
		";
	}
?>