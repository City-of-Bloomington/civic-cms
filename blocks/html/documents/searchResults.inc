<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param object $this->results
 */
?>
<h1>Search Results</h1>
<?php
	if (count($this->results))
	{
		# If we've got a lot of results, split them up into seperate pages
		if (count($this->results) > 10)
		{
			$this->results = new ArrayObject($this->results);
			if (!isset($_GET['page'])) { $_GET['page'] = 0; }
			$pages = new Paginator($this->results,10);
			$results = new LimitIterator($this->results->getIterator(),$pages[$_GET['page']],$pages->getPageSize());
		}
		else { $results = $this->results; }

		# Show the results
		foreach($results as $document)
		{
			$title = View::escape($document->getTitle());

			if ($document->getDescription()) { $description = View::escape($document->getDescription()); }
			else { $description = substr(strip_tags($document->getContent('en')),0,160).'...'; }

			$size_in_bytes = strlen($document->getContent('en'));
			if ($size_in_bytes>1000)
			{
				$size = round($size_in_bytes/1024);
				$size.='k';
			}
			else { $size = $size_in_bytes.'bytes'; }


			echo "
			<div id=\"searchResult\">
				<h2><a href=\"{$document->getURL()}\">$title</a></h2>
				<p>$description</p>
				<span><a href=\"{$document->getURL()}\">".BASE_URL."/{$document->getWikiTitle()}</a> - $size
					- last updated {$document->getModified('%D')}</span>
			</div>
			";
		}
	}
	else
	{
		echo '<p>We were unable to find any documents that match your search terms.</p>';
	}

	if (isset($pages)) { include FRAMEWORK.'/pageNavigation.inc'; }
?>
