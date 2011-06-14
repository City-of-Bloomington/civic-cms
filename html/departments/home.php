<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 */
	$departmentList = new DepartmentList();
	$departmentList->find();

	$template = new Template();
	$template->blocks[] = new Block('departments/departmentList.inc',array('departmentList'=>$departmentList));
	echo $template->render();
?>