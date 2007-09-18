<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
	verifyUser();
	$template = new Template('backend');

	$sort = isset($_GET['sort']) ? urldecode($_GET['sort']) : null;

	$fields = array();
	if (isset($_GET['mime_type']) && $_GET['mime_type']) { $fields['mime_type'] = $_GET['mime_type']; }
	if (isset($_GET['department_id']) && $_GET['department_id']) { $fields['department_id'] = $_GET['department_id']; }
	if (!count($fields)) { $fields = null; }


	$mediaList = new MediaList();
	$mediaList->find($fields,$sort);

	$template->blocks[] = new Block('media/mediaList.inc',array('mediaList'=>$mediaList));
	$template->render();
?>
