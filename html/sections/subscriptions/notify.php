<?php
/**
 * @copyright Copyright (C) 2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET document_id
 * @param GET return_url
 */
verifyUser();

$document = new Document($_REQUEST['document_id']);
if ($document->permitsEditingBy($_SESSION['USER']))
{
	if (isset($_POST['message']))
	{
		foreach($document->getSections() as $section)
		{
			foreach($section->getSubscriptions() as $subscription)
			{
				$message = $_POST['message'].="\n\n".$document->getURL();

				$to = $subscription->getUser()->getEmail();
				$headers = "From: ".APPLICATION_NAME;
				mail($to,$section->getName()." subscription",$message,$headers);
			}
		}
		Header("Location: $_REQUEST[return_url]");
	}
	else
	{
		$form = new Block('sections/subscriptions/notificationForm.inc');
		$form->document = $document;
		$form->return_url = $_REQUEST['return_url'];

		$template = new Template();
		$template->blocks[] = $form;
		$template->render();
	}
}
else
{
	$_SESSION['errorMessages'][] = new Exception('noAccessAllowed');
	Header("Location: $_REQUEST[return_url]");
}
