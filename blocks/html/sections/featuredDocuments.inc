<?php
/**
 * @copyright Copyright (C) 2007-2008 City of Bloomington, Indiana. All rights reserved.
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
	<?php
		foreach($this->documentList as $document)
		{
			$title = $document->getFeature_title() ? View::escape($document->getFeature_title()) : View::escape($document->getTitle());
			$description = View::escape($document->getDescription());
			
			if ($document->getIcon_media())
			{
				$icon = WikiMarkup::parse("[thumbnail:{$document->getIcon_media_id()},left]");
			}
			elseif($document->getDocumentType()->getMedia_id())
			{
				$icon = WikiMarkup::parse("[thumbnail:{$document->getDocumentType()->getMedia_id()},left]");
			}
			else { $icon = ''; }
			

			echo "
			<div>
				<h4><a href=\"{$document->getURL()}\">$title</a></h4>
				$icon
				<p>$description</p>
			</div>
			";
		}
	?>
</div>
