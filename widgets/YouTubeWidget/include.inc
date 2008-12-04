<?php
/**
 * @copyright Copyright (C) 2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param string $this->XMLFeedURL;
 * @param int $this->numVideosToDisplay;
 */
?>
<script type="text/javascript" src="http://www.google.com/jsapi?key=<?php echo GOOGLE_API_KEY; ?>"></script>
<script type="text/javascript">
	google.load("feeds", "1");

	function initialize()
	{
		setYouTubeFeed("<?php echo $this->XMLFeedURL; ?>", "youtube_widget");
	}
	google.setOnLoadCallback(initialize);


	function setYouTubeFeed(loc, divID)
	{
		var feed = new google.feeds.Feed(loc);
		feed.setResultFormat(google.feeds.Feed.MIXED_FORMAT);

		feed.load(function(result)
		{
			if (!result.error)
			{
				var widget = document.getElementById(divID);

				var ul = document.createElement('ul');

				var count = 0;
				for (var i = 0; i < result.feed.entries.length; i++)
				{
					count++;
					if (count > <?php echo $this->numVideosToDisplay; ?>) break;

					var entry = result.feed.entries[i];

					var thumbElement = google.feeds.getElementsByTagNameNS(entry.xmlNode, 'http://search.yahoo.com/mrss/', 'thumbnail')[0];
					var thumbSRC = thumbElement.getAttribute('url');

					var linkval = entry.link;

					var li = document.createElement('li');

					if(thumbSRC)
					{
						var span = document.createElement('span');
						span.setAttribute('class','image thumbnail');
						span.className = 'image thumbnail';

						var ahref = document.createElement('a');
						ahref.setAttribute('href', linkval);

						var imgNode = document.createElement('img');
						imgNode.setAttribute('src', thumbSRC);

						ahref.appendChild(imgNode);
						span.appendChild(ahref);
						li.appendChild(span);
					}

					title = document.createElement('a');
					title.setAttribute('href',linkval);
					title.setAttribute('class','title');
					title.className = 'title';
					title.appendChild(document.createTextNode(entry.title));
					li.appendChild(title);

					ul.appendChild(li);
				}
				widget.appendChild(ul);
			}
		});
	}
</script>
<div class="youtube widget" id="youtube_widget">
	<h1>YouTube Videos</h1>
	<div class="channelLink"><a href="http://www.youtube.com/cityofbloomington">View All Videos</a></div>
</div>
