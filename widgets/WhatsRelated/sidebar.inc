<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
?>
<div><div class="titleBar">What's Related</div>
<ul>
<?php
	foreach($this->document->getRelatedDocuments() as $document)
	{
		echo "<li><a href=\"".BASE_URL."/documents/viewDocument.php?document_id={$document->getId()}\">{$document->getTitle()}</a></li>";
	}
?>
</ul>
</div>