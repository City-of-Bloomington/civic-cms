<?php
/**
 * @copyright Copyright (C) 2007-2008 City of Bloomington, Indiana. All rights reserved.
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

	$currentType = (isset($_GET['type']) && in_array($_GET['type'],array_keys($results))) ? $_GET['type'] : 'Documents';

	if (isset($results[$currentType]) && count($results[$currentType]))
	{
		# If we've got a lot of results, split them up into seperate pages
		if ($results[$currentType] > 10)
		{
			$resultArray = new ArrayObject($results[$currentType]);
			$pages = new Paginator($resultArray,10);

			# Make sure we're asking for a page that actually exists
			$page = (isset($_GET['page']) && $_GET['page']) ? (int)$_GET['page'] : 0;
			if (!$pages->offsetExists($page)) { $page = 0; }

			$resultsList = new LimitIterator($resultArray->getIterator(),$pages[$page],$pages->getPageSize());
		}
		else { $resultsList = $this->results[$currentType]; }
	}
	else
	{
		$resultsList = array();
	}
}
else { $_GET['search'] = ''; }

$template = new Template();
$template->blocks[] = new Block('search/searchForm.inc',array('search'=>$_GET['search']));
if (isset($results))
{
	# Pass all the results to the Tab block
	$resultsTab = new Block('search/resultTabs.inc');
	$resultsTab->currentType = $currentType;
	$resultsTab->results = $results;
	$template->blocks[] = $resultsTab;

	# Only pass the results you want displayed to the results block
	$resultBlock = new Block('search/results.inc');
	$resultBlock->results = $resultsList;
	$resultBlock->currentType = $currentType;
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
