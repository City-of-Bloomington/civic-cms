<?php
/**
 * @copyright 2007-2009 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET grep
 */
verifyUser(array('Administrator','Webmaster'));
$template = new Template();
$template->blocks[] = new Block('documents/grepForm.inc');

if (isset($_GET['grep'])) {
	$list = new DocumentList();
	$errors = $list->grep($_GET['grep']);
	if ($errors) {
		$template->blocks[] = new Block('documents/grepErrors.inc',array('errors'=>$errors));
	}

	// If we've got a lot of results, split them up into seperate pages
	if (count($list) > 10) {
		$pages = $list->getPagination(10);
		$page = (isset($_GET['page']) && $_GET['page']) ? (int)$_GET['page'] : 0;
		if (!$pages->offsetExists($page)) {
			$page = 0;
		}
		$resultsList = new LimitIterator($list->getIterator(),$pages[$page],$pages->getPageSize());
	}
	else {
		$resultsList = $list;
	}

	$resultBlock = new Block('search/results.inc');
	$resultBlock->results = $resultsList;
	$resultBlock->currentType = 'Documents';
	$resultBlock->type = 'documents';
	$template->blocks[] = $resultBlock;


	if (isset($pages)) {
		$pageNavigation = new Block('pageNavigation.inc');
		$pageNavigation->page = $page;
		$pageNavigation->pages = $pages;
		$pageNavigation->url = new URL("$_SERVER[SERVER_NAME]$_SERVER[REQUEST_URI]");

		$template->blocks[] = $pageNavigation;
	}
}
echo $template->render();
