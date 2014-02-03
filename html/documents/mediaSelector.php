<?php
/**
 * @copyright 2007-2014 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
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
if (count($mediaList) > 50) {
	$page = !empty($_GET['page']) ? (int)$_GET['page'] : 1;
	$media = $mediaList->getPagination(50);
	$media->setCurrentPageNumber($page);
}
else { $media = $mediaList; }

# Render the page
$template = new Template('mediaBrowser');
$template->blocks[] = new Block('documents/mediaSelector.inc',array('mediaList'=>$media,'department'=>$department));
if (count($mediaList) > 50) {
	$template->blocks[] = new Block('pageNavigation.inc', ['paginator'=>$media]);
}
echo $template->render();
