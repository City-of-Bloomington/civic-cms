<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
	$template = new Template();

	$attachments = new AttachmentList();
	isset($_GET['sort']) ? $attachments->find(null,$_GET['sort']) : $attachments->find();

	$template->blocks[] = new Block('media/attachmentList.inc',array('attachmentList'=>$attachments));
	$template->render();
?>