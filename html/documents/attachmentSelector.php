<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
	verifyUser(array('Administrator','Webmaster','Content Creator','Publisher'));

	$department_id = isset($_GET['department_id']) ? $_GET['department_id'] : $_SESSION['USER']->getDepartment_id();
	$department = new Department($department_id);
	$attachments = new AttachmentList(array('department_id'=>$department_id));

	$template = new Template('mediaBrowser');
	$template->blocks[] = new Block('documents/attachmentSelector.inc',array('attachmentList'=>$attachments,'department'=>$department));
	$template->render();
?>