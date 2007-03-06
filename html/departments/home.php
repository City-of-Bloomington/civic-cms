<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
	$departmentList = new DepartmentList();
	$departmentList->find();

	$template = new Template();
	$template->blocks[] = new Block('departments/departmentList.inc',array('departmentList'=>$departmentList));
	$template->render();
?>