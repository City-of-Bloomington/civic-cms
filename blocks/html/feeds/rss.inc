<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
?>
<h2>RSS Feeds</h2>
<p>RSS feeds assist persons interested in keeping track of changes to a website.
Often, RSS feeds are used to keep track of news releases or blog entries.
Websites usually divide their feeds up into topics, so that you can keep track
of your areas of interest, specifically.  By subscribing to an RSS feed, you can
keep track of all updates to the portions of the website that interest you without
hunting it down or event visiting the website!</p>
<p>To subscribe to an RSS feed, you need an RSS Reader,
<a href="http://dir.yahoo.com/Computers_and_Internet/Data_Formats/XML__eXtensible_Markup_Language_/RSS/RSS_Readers_and_Aggregators/">see Yahoo's list of RSS Readers</a>.
The homepage you've set for your browser might have an area for RSS feeds, as well
(such as Yahoo, Google, or AOL.  You can also view the RSS feed as a list by
clicking the feed.</p>

<table>
<?php
	$list = new DocumentTypeList();
	$list->find();
	foreach($list as $type)
	{
		$name = View::escape($type->getType());
		$url = BASE_URL.'/documentTypes/documents.php?format=rss;documentType_id='.$type->getId();
		echo "<tr><th>$name</th><td><a href=\"$url\">$url</a></td></tr>";
	}
?>
</table>
