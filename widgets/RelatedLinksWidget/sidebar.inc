<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Section $this->section
 * @param Document $this->document
 */
	$links = $this->section->getDocumentLinks();
	if (count($links))
	{
		echo '<div><div class="titleBar">Related Links</div><ul>';
		foreach($links as $link)
		{
			echo "<li><a href=\"{$link->getHref()}\">{$link->getTitle()}</a></li>";
		}
		echo '</ul></div>';
	}
?>