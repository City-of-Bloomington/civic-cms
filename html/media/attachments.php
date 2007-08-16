<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
	$template = new Template();

	$mediaList = new MediaList(array('media_type'=>'attachment'));

	$sort = null;
	$search = null;
	if (isset($_GET['sort'])) { $sort = $_GET['sort']; }
	if (isset($_GET['department_id'])) { $search = array('department_id'=>$_GET['department_id']); }

	$mediaList->find($search,$sort);


	$template->blocks[] = new Block('media/mediaList.inc',array('mediaList'=>$mediaList));
	$template->render();
?>