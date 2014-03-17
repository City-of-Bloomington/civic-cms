<?php
/**
 * @copyright 2007-2014 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param DocumentType $this->documentType
 * @param DocumentList $this->documents
 */
?>
<channel>
	<title><?php echo View::escape($this->documentType); ?></title>
	<link><?php echo 'http://'.$_SERVER['SERVER_NAME'].$_SERVER['REQUEST_URI']; ?></link>
<?php
	if (count($this->documents)) {
		foreach($this->documents as $document) {
			# Use the publishDate from the first document in the list as the pubDate for the feed
			if (!isset($pubDate))
			{
				$pubDate = date('D, j M Y',strtotime($document->getPublishDate()));
				echo "<pubDate>$pubDate</pubDate>";
			}
			else { $pubDate = date('D, j M Y',strtotime($document->getPublishDate())); }

			$title = View::escape($document->getTitle());
			$link = $document->getURL();

			$lang = !empty($_SESSION['LANGUAGE']) ? $_SESSION['LANGUAGE'] : 'en';

			# Use only the first 30 words of the document
			$description = '';
			$text = $document->getContent($lang);
			if (!empty($text)) {
				$words = preg_split('/\s+/',strip_tags($text));
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
