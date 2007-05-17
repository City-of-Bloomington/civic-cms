<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
/*
	$this->section
*/
?>
<div class="interfaceBox">
	<div class="titleBar">Documents</div>
	<ul>
	<?php
		foreach($this->section->getDocuments() as $document)
		{
			echo "<li><a href=\"".BASE_URL."/documents/viewDocument.php?document_id={$document->getId()}\">{$document->getId()}</a></li>";
		}
	?>
	</ul>
</div>