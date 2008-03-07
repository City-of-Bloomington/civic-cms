<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Section $this->section
 * @param DocumentList $this->documentList
 * @param DocumentType $this->documentType
 */
	$type = Inflector::pluralize($this->documentType->getType());
	$sectionName = View::escape($this->section->getName());
?>
<div class="interfaceBox featured">
	<h2><?php
			echo "Spotlight $type in $sectionName";
		?>
	</h2>
	<table>
	<?php
		foreach($this->documentList as $document)
		{
			$title = $document->getFeature_title() ? View::escape($document->getFeature_title()) : View::escape($document->getTitle());
			$description = View::escape($document->getDescription());
			$icon = $document->getDocumentType()->getMedia_id() ? "<img src=\"".BASE_URL."/media/media.php?size=thumbnail;media_id={$document->getDocumentType()->getMedia_id()}\" />" : '';

			echo "
			<tr><th>$icon</th>
				<td><h4><a href=\"{$document->getURL()}\">$title</a></h4>
					<p>$description</p>
				</td>
			</tr>
			";
		}
	?>
	</table>
</div>
