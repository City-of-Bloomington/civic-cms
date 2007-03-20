<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
	$template = new Template();

	$attachments = new AttachmentList();

	$sort = null;
	$search = null;
	if (isset($_GET['sort'])) { $sort = $_GET['sort']; }
	if (isset($_GET['department_id'])) { $search = array('department_id'=>$_GET['department_id']); }

	$attachments->find($search,$sort);


	$template->blocks[] = new Block('media/attachmentList.inc',array('attachmentList'=>$attachments));
	$template->render();
?>