<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param object $this->results
 */
?>
<h2>Search Results</h2>
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
		echo '<div id="searchResults">';
		foreach($results as $document)
		{
			$title = View::escape($document->getTitle());
			$description = View::escape($document->getDescription());
			echo "
			<h2><a href=\"".BASE_URL."/documents/viewDocument.php?document_id={$document->getId()}\">$title</a></h2>
			<p>$description</p>
			";
		}
		echo '</div>';
	}
	else
	{
		echo '<p>We were unable to find any documents that match your search terms.</p>';
	}

	if (isset($pages)) { include FRAMEWORK.'/pageNavigation.inc'; }
?>