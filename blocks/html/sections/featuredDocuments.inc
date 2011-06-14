<?php
/**
 * @copyright Copyright (C) 2007-2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
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
			
			$icon = false;
			if ($document->getIcon_media())
			{
				$icon = $document->getIcon_media();
			}
			elseif($document->getDocumentType()->getMedia_id())
			{
				$icon = $document->getDocumentType()->getMedia();
			}
			
			if ($icon)
			{
				$alt = View::escape($icon->getTitle());
				$img = "<img src=\"{$icon->getURL('icon')}\" alt=\"$alt\" />";
			}
			else { $img = ''; }
			
			echo "
			<tr><th colspan=\"2\"><h4><a href=\"{$document->getURL()}\">$title</a></h4></th></tr>
			<tr><td>$img</td>
				<td><p>$description</p></td>
			</tr>
			";
		}
	?>
	</table>
</div>
