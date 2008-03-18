<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param object $this->results
 * @param string $this->currentType
 * @param string $this->type
 */
if (count($this->results))
{
	# Show the results
	foreach($this->results as $hit)
	{
		#------------------------------------------------------------
		# Document Results
		#------------------------------------------------------------
		if ($hit instanceof Document)
		{
			if ($hit->isActive())
			{
				$title = View::escape($hit->getTitle());

				if ($hit->getDescription()) { $description = View::escape(strip_tags($hit->getDescription())); }
				else
				{
					$description = '';
					$words = preg_split('/\s+/',strip_tags($hit->getContent('en')));
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

				$size_in_bytes = strlen($hit->getContent('en'));
				if ($size_in_bytes>1000)
				{
					$size = round($size_in_bytes/1024);
					$size.='k';
				}
				else { $size = $size_in_bytes.'bytes'; }


				echo "
				<div class=\"searchResult\">
					<h3><a href=\"{$hit->getURL()}\">$title</a></h3>
					<p>$description</p>
					<span><a href=\"{$hit->getURL()}\">".BASE_URL."/{$hit->getWikiTitle()}</a> - $size
						- last updated {$hit->getModified('%D')}</span>
				</div>
				";
			}
		}
		#------------------------------------------------------------
		# Event Results
		#------------------------------------------------------------
		elseif ($hit instanceof Event)
		{
			$title = View::escape($hit->getTitle());
			$description = View::escape(strip_tags($hit->getDescription()));
			echo "
			<div id=\"searchResult\">
				<h3><a href=\"{$hit->getURL()}\">$title</a></h3>
				<p>$description</p>
				<span>last updated {$hit->getModified('%D')}</span>
			</div>
			";
		}

		#------------------------------------------------------------
		# Media Results
		#------------------------------------------------------------
		elseif ($hit instanceof Media)
		{
			$title = View::escape($hit->getTitle());
			$description = View::escape(strip_tags($hit->getDescription()));
			$class = $hit->getExtension();
			echo "
			<div id=\"searchResult\">
				<h3><a href=\"{$hit->getURL('original')}\" class=\"$class\">$title</a></h3>
				<p>$description</p>
				<span>uploaded {$hit->getUploaded('%D')}</span>
			</div>
			";
		}
	}
}
else
{
	echo '<p>We were unable to find anything that matches your search terms.</p>';
}
