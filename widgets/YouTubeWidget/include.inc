<?php
/**
 * @copyright Copyright (C) 2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
?>
<div class="youtube widget">
	<h1>YouTube Videos</h1>
	<ul>
	<?php
		$c = 0;
		/**
		 * RSS Feeds from YouTube
		 */
		if ($this->xml->channel)
		{
			foreach($this->xml->channel->item as $item)
			{
				if ($c < $this->numVideosToDisplay)
				{
					$media = $item->children('http://search.yahoo.com/mrss/');
					$thumbnail = $media->thumbnail->attributes();
					echo "
					<li><span class=\"image thumbnail\">
							<a href=\"{$item->link}\">
								<img src=\"{$thumbnail['url']}\" />
							</a>
						</span>
						<a class=\"title\" href=\"{$item->link}\">
							{$item->title}
						</a>
					</li>
					";
					$c++;
				}
				else { break; }
			}
		}
		/**
		 * Atom Feeds from YouTube
		 */
		if ($this->xml->entry)
		{
			foreach($this->xml->entry as $entry)
			{
				if ($c < $this->numVideosToDisplay)
				{
					$media = $entry->children('http://search.yahoo.com/mrss/');
					$group = $media->group;
					$player = $group->player->attributes();

					$thumbnail = $group->thumbnail[0]->attributes();
					echo "
					<li><span class=\"image thumbnail\">
							<a href=\"$player[url]\">
								<img src=\"$thumbnail[url]\" />
							</a>
						</span>
						<a class=\"title\" href=\"$player[url]\">
							{$entry->title}
						</a>
					</li>
					";
					$c++;
				}
				else { break ; }
			}
		}
	?>
	</ul>
	<p class="channelLink"><a href="http://www.youtube.com/cityofbloomington">View All Videos</a></p>
</div>
