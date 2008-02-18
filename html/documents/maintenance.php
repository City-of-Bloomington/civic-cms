<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET grep
 */
verifyUser(array('Administrator','Webmaster'));

if (isset($_GET['grep']))
{
	$list = new DocumentList();
	$list->grep($_GET['grep']);

	# If we've got a lot of results, split them up into seperate pages
	if (count($list) > 10)
	{
		$pages = $list->getPagination(10);
		$page = (isset($_GET['page']) && $_GET['page']) ? (int)$_GET['page'] : 0;
		if (!$pages->offsetExists($page)) { $page = 0; }
		$resultsList = new LimitIterator($list->getIterator(),$pages[$page],$pages->getPageSize());
	}
	else { $resultsList = $list; }

	$resultBlock = new Block('search/results.inc');
	$resultBlock->results = $resultsList;
	$resultBlock->currentType = 'Documents';
	$resultBlock->type = 'documents';
}


$template = new Template();
$template->blocks[] = new Block('documents/grepForm.inc');
if (isset($resultBlock))
{
	$template->blocks[] = $resultBlock;

	if (isset($pages))
	{
		$pageNavigation = new Block('pageNavigation.inc');
		$pageNavigation->page = $page;
		$pageNavigation->pages = $pages;
		$pageNavigation->url = new URL("$_SERVER[SERVER_NAME]$_SERVER[REQUEST_URI]");

		$template->blocks[] = $pageNavigation;
	}
}
echo $template->render();
