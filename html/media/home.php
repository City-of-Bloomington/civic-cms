<?php
/**
 * @copyright 2007-2014 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
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
	if (count($mediaList) > 50) {
		$page = !empty($_GET['page']) ? (int)$_GET['page'] : 1;
		$media = $mediaList->getPagination(50);
		$media->setCurrentPageNumber($page);
	}
	else { $media = $mediaList; }

	$template = new Template('backend');
	$template->blocks[] = new Block('media/mediaList.inc',array('mediaList'=>$media));
	if (count($mediaList) > 50) {
		$template->blocks[] = new Block('pageNavigation.inc', ['paginator'=>$media]);
	}
	echo $template->render();
