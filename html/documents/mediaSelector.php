<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
verifyUser(array('Administrator','Webmaster','Content Creator','Publisher'));

# We want the user to always be in their department by default
$department = isset($_GET['department_id']) ? new Department($_GET['department_id']) : $_SESSION['USER']->getDepartment();

# Check for any filters the user has applied
$fields = array();
$fields['department_id'] = $department->getId();
if (isset($_GET['mime_type']) && $_GET['mime_type']) { $fields['mime_type'] = $_GET['mime_type']; }
if (!count($fields)) { $fields = null; }

# Check for the sorting the user has applied
$sort = isset($_GET['sort']) ? urldecode($_GET['sort']) : null;

# Get the list of media
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



# Render the page
$template = new Template('mediaBrowser');
$template->blocks[] = new Block('documents/mediaSelector.inc',array('mediaList'=>$media,'department'=>$department));
if (isset($pages))
{
	$pageNavigation = new Block('pageNavigation.inc');
	$pageNavigation->page = $page;
	$pageNavigation->pages = $pages;
	$pageNavigation->url = new URL($_SERVER['SERVER_NAME'].$_SERVER['REQUEST_URI']);

	$template->blocks[] = $pageNavigation;
}
echo $template->render();
