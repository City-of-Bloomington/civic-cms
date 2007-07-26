<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param object $this->results
 */
?>
<h2>Search Results</h2>
<ul>
<?php
	foreach($this->results as $document)
	{
		$title = View::escape($document->getTitle());
		echo "<li><a href=\"".BASE_URL."/documents/viewDocument.php?document_id={$document->getId()}\">$title</a></li>";
	}
?>
</ul>
