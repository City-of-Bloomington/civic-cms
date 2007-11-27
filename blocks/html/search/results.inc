<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param object $this->results
 * @param string $this->currentType
 */
	$currentType = isset($this->currentType) ? Inflector::pluralize($this->currentType) : 'Documents';
	$type = strtolower($currentType);
?>
<h1>Search Results</h1>
<div class="tabBar">
	<ul>
	<?php
		$url = new URL("http://$_SERVER[SERVER_NAME]$_SERVER[REQUEST_URI]");

		$url->type = 'Document';
		$class = $currentType=='Documents' ? 'class="current"' : '';
		$count = isset($this->results['documents']) ? count($this->results['documents']) : 0;
		echo "<li $class><a href=\"$url\">Documents</a> ($count)</li>";

		$url->type = 'Event';
		$class = $currentType=='Events' ? 'class="current"' : '';
		$count = isset($this->results['events']) ? count($this->results['events']) : 0;
		echo "<li $class><a href=\"$url\">Events</a> ($count)</li>";
	?>
	</ul>
</div>
<?php
	if (count($this->results))
	{
		if (isset($this->results[$type]) && count($this->results[$type]))
		{
			# If we've got a lot of results, split them up into seperate pages
			if (count($this->results[$type]) > 10)
			{
				$resultArray = new ArrayObject($this->results[$type]);
				if (!isset($_GET['page'])) { $_GET['page'] = 0; }
				$pages = new Paginator($resultArray,10);
				$results = new LimitIterator($resultArray->getIterator(),$pages[$_GET['page']],$pages->getPageSize());
			}
			else { $results = $this->results[$type]; }

			# Show the results
			foreach($results as $hit)
			{
				if ($hit instanceof Document)
				{
					$title = View::escape($hit->getTitle());

					if ($hit->getDescription()) { $description = View::escape($hit->getDescription()); }
					else { $description = substr(strip_tags($hit->getContent('en')),0,160).'...'; }

					$size_in_bytes = strlen($hit->getContent('en'));
					if ($size_in_bytes>1000)
					{
						$size = round($size_in_bytes/1024);
						$size.='k';
					}
					else { $size = $size_in_bytes.'bytes'; }


					echo "
					<div id=\"searchResult\">
						<h3><a href=\"{$hit->getURL()}\">$title</a></h3>
						<p>$description</p>
						<span><a href=\"{$hit->getURL()}\">".BASE_URL."/{$hit->getWikiTitle()}</a> - $size
							- last updated {$hit->getModified('%D')}</span>
					</div>
					";
				}
				elseif ($hit instanceof Event)
				{
					$title = View::escape($hit->getTitle());
					$description = View::escape($hit->getDescription());
					echo "
					<div id=\"searchResult\">
						<h3><a href=\"{$hit->getURL()}\">$title</a></h3>
						<p>$description</p>
						<span>last updated {$hit->getModified('%D')}</span>
					</div>
					";

				}
			}
		}
	}
	else
	{
		echo '<p>We were unable to find anything that matches your search terms.</p>';
	}

	if (isset($pages)) { include FRAMEWORK.'/pageNavigation.inc'; }
?>
