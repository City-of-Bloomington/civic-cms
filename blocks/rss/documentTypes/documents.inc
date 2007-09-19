<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param DocumentType $this->documentType
 * @param TagGroup $this->tagGroup
 */
	$type = View::escape($this->documentType->getType());
	$href = new URL(BASE_URL.'/documentTypes/documents.php');
	$href->parameters['documentType_id'] = $this->documentType->getId();
	$href->parameters['tagGroup_id'] = 'none';
?>
<channel>
	<title><?php echo $type; ?></title>
	<link><?php echo $this->url; ?></link>
<?php
	$documents = $this->documentType->getDocuments('publishDate desc');
	if (count($documents))
	{
		foreach($documents as $document)
		{
			# Use the publishDate from the first document in the list as the pubDate for the feed
			if (!isset($pubDate))
			{
				$pubDate = date('D, j M Y',strtotime($document->getPublishDate()));
				echo "<pubDate>$pubDate</pubDate>";
			}
			else { $pubDate = date('D, j M Y',strtotime($document->getPublishDate())); }

			$title = View::escape($document->getTitle());
			$link = $document->getURL();
			#$description = View::escape($document->getDescription());
			$description = View::escape(WikiMarkup::parse(substr(strip_tags($document->getContent($_SESSION['LANGUAGE'])),0,255)));
			echo "
			<item>
				<title>$title</title>
				<link>$link</link>
				<pubDate>$pubDate</pubDate>
				<description>$description</description>
			</item>
			";
		}
	}
?>
</channel>
