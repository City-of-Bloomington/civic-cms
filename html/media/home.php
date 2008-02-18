<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
	verifyUser();

	$sort = isset($_GET['sort']) ? urldecode($_GET['sort']) : null;

	$fields = array();
	if (isset($_GET['mime_type']) && $_GET['mime_type']) { $fields['mime_type'] = $_GET['mime_type']; }
	if (isset($_GET['department_id']) && $_GET['department_id']) { $fields['department_id'] = $_GET['department_id']; }
	if (!count($fields)) { $fields = null; }




	$mediaList = new MediaList();
	$mediaList->find($fields,$sort);
	# For long lists, paginate the results
	if (count($mediaList) > 50)
	{
		$pages = $mediaList->getPagination(50);

		# Make sure we're asking for a page that actually exists
		$page = (isset($_GET['page']) && $_GET['page']) ? (int)$_GET['page'] : 0;
		if (!$pages->offsetExists($page)) { $page = 0; }

		$media = new LimitIterator($mediaList->getIterator(),$pages[$page],$pages->getPageSize());
	}
	else { $media = $mediaList; }






	$template = new Template('backend');
	$template->blocks[] = new Block('media/mediaList.inc',array('mediaList'=>$media));
	if (isset($pages))
	{
		$pageNavigation = new Block('pageNavigation.inc');
		$pageNavigation->page = $page;
		$pageNavigation->pages = $pages;
		$pageNavigation->url = new URL($_SERVER['SERVER_NAME'].$_SERVER['REQUEST_URI']);

		$template->blocks[] = $pageNavigation;
	}
	echo $template->render();
