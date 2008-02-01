<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param DocumentType $this->documentType
 * @param FacetGroup $this->facetGroup
 */
	$type = View::escape($this->documentType->getType());
	$href = new URL(BASE_URL.'/documentTypes/documents.php');
	$href->parameters['documentType_id'] = $this->documentType->getId();
	$href->parameters['facetGroup_id'] = 'none';
?>
<channel>
	<title><?php echo $type; ?></title>
	<link><?php echo $this->url; ?></link>
<?php
	$documents = new DocumentList();
	$documents->find(array('documentType_id'=>$this->documentType->getId()),'publishDate desc');
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

			# Use only the first 30 words of the document
			$description = '';
			$words = preg_split('/\s+/',strip_tags($document->getContent($_SESSION['LANGUAGE'])));
			$c = 0;
			foreach($words as $word)
			{
				$description.= "$word ";
				$c++;
				if ($c >= 30)
				{
					$description.=  "...";
					break;
				}
			}
			$description = View::escape(WikiMarkup::parse($description));

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
