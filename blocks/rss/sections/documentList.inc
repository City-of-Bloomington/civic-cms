<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Section $this->documentList
 * @param string $this->title
 * @param URL $this->url
 */
?>
<channel>
	<title><?php echo View::escape($this->title); ?></title>
	<link><?php echo $this->url; ?></link>
	<?php
		foreach($this->documentList as $document)
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
			$id = $document->getID();

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
				<id>$id</id>
				<pubDate>$pubDate</pubDate>
				<description>$description</description>
			</item>
			";
		}
	?>
</channel>
