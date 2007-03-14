<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET document_id
 */
	if (isset($_GET['document_id'])) { $document = new Document($_GET['document_id']); }
	if (isset($_FILES['attachment']))
	{
		$attachment = new Attachment();
		$attachment->setTitle($_POST['attachment']['title']);
		$attachment->setDescription($_POST['attachment']['description']);

		$document = new Document($_POST['document_id']);
		$attachment->addDocument($document);

		try
		{
			$attachment->setFile($_FILES['attachment']);
			$attachment->save();
		}
		catch(Exception $e) { $_SESSION['errorMessages'][] = $e; }
	}


	$template = new Template();
	$template->blocks[] = new Block('documents/documentInfo.inc',array('document'=>$document));

	$attachments = new AttachmentList(array('document_id'=>$document->getId()));
	$template->blocks[] = new Block('media/attachmentList.inc',array('attachmentList'=>$attachments));

	if (isset($_SESSION['USER']) && $document->permitsEditingBy($_SESSION['USER']))
	{
		$template->blocks[] = new Block('documents/addAttachmentForm.inc',array('document'=>$document));
	}

	$template->render();
?>