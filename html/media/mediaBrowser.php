<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
 	verifyUser();

	$department_id = isset($_GET['department_id']) ? $_GET['department_id'] : $_SESSION['USER']->getDepartment_id();
	$department = new Department($department_id);
	$mediaList = new MediaList(array('department_id'=>$department_id));

	$template = new Template('mediaBrowser');
	$template->blocks[] = new Block('media/mediaList.inc',array('mediaList'=>$mediaList,'department'=>$department));
	$template->render();
?>