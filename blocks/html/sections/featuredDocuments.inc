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
	<table>
	<?php
		foreach($this->documentList as $document)
		{
			$title = $document->getFeature_title() ? View::escape($document->getFeature_title()) : View::escape($document->getTitle());
			$description = View::escape($document->getDescription());
			echo "
			<tr><th><img src=\"".BASE_URL."/documents/icon.php?document_id={$document->getId()}\" alt=\"$title\" /></th>
				<td><h4><a href=\"{$document->getURL()}\">$title</a></h4>
					$description
				</td>
			</tr>
			";
		}
	?>
	</table>
</div>
