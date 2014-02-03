<?php
/**
 * @copyright 2007-2014 City of Bloomington, Indiana
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
		$page = !empty($_GET['page']) ? (int)$_GET['page'] : 1;
		$resultsList = $list->getPagination(10);
		$resultsList->setCurrentPageNumber($page);
	}
	else {
		$resultsList = $list;
	}

	$template->blocks[] = new Block('search/results.inc', ['results'=>$resultsList]);

	if (count($list) > 10) {
		$template->blocks[] = new Block('pageNavigation.inc', ['paginator'=>$resultsList]);
	}
}
echo $template->render();
