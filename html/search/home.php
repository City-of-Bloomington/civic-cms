<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET search
 * @param GET type Document, Event
 */

if (isset($_GET['search']) && $_GET['search'])
{
	try
	{
		$search = new Search();
		$results = $search->find($_GET['search']);
	}
	catch (Exception $e) { exception_handler($e); }


	$currentType = isset($_GET['type']) ? Inflector::pluralize($_GET['type']) : 'Documents';
	$type = strtolower($currentType);

	if (isset($results[$type]) && count($results[$type]))
	{
		# If we've got a lot of results, split them up into seperate pages
		if ($results[$type] > 10)
		{
			$resultArray = new ArrayObject($results[$type]);
			$pages = new Paginator($resultArray,10);

			# Make sure we're asking for a page that actually exists
			$page = (isset($_GET['page']) && $_GET['page']) ? (int)$_GET['page'] : 0;
			if (!$pages->offsetExists($page)) { $page = 0; }

			$resultsList = new LimitIterator($resultArray->getIterator(),$pages[$page],$pages->getPageSize());
		}
		else { $resultsList = $this->results[$type]; }
	}
	else { $resultsList = array(); }
}



$template = new Template();
$template->blocks[] = new Block('search/searchForm.inc',array('search'=>$_GET['search']));
if (isset($results))
{
	$resultsTab = new Block('search/resultTabs.inc');
	$resultsTab->currentType = $currentType;
	$resultsTab->type = $type;
	$resultsTab->results = $results;

	$resultBlock = new Block('search/results.inc');
	$resultBlock->results = $resultsList;
	$resultBlock->currentType = $currentType;
	$resultBlock->type = $type;

	$template->blocks[] = $resultsTab;
	$template->blocks[] = $resultBlock;

	if (isset($pages))
	{
		$pageNavigation = new Block('pageNavigation.inc');
		$pageNavigation->page = $page;
		$pageNavigation->pages = $pages;
		$pageNavigation->url = new URL($_SERVER['SERVER_NAME'].$_SERVER['REQUEST_URI']);

		$template->blocks[] = $pageNavigation;
	}
}
echo $template->render();
