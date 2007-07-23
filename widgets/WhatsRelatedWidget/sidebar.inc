<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Document $this->document
 */
?>
<div><div class="titleBar">What's Related</div>
<ul>
<?php
	foreach($this->document->getRelatedDocuments() as $document)
	{
		$title = View::escape($document->getTitle();
		echo "<li><a href=\"{$document->getURL()}\">$title</a></li>";
	}
?>
</ul>
</div>
