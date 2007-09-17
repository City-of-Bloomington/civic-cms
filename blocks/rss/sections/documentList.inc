<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
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
	?>
</channel>
