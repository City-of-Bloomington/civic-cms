<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param DocumentList $this->documentList
 * @param DocumentType $this->documentType (optional)
 */
	$type = isset($this->documentType) ? $this->documentType->getType() : 'Documents';
?>
<div class="interfaceBox">
	<div class="titleBar">Featured <?php echo $type; ?></div>
	<ul>
	<?php
		foreach($this->documentList as $document)
		{
			echo "
			<li><a href=\"".BASE_URL."/documents/viewDocument.php?document_id={$document->getId()}\">
				{$document->getTitle()}</a>
			</li>
			";
		}
	?>
	</ul>
</div>
