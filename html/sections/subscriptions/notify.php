<?php
/**
 * @copyright Copyright (C) 2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET section_id
 * @param GET return_url
 */
verifyUser();
/*
$section = new Section($_REQUEST['section_id']);

if ($section->permitsPostingBy($_SESSION['USER']))
{
	if (isset($_POST['message']))
	{
		$documents = array();
		if (isset($_POST['documents']))
		{
			foreach($_POST['documents'] as $id=>$checked)
			{
				$documents[] = new Document($id);
			}
		}

		$email = new Template('email','text');
		$notification = new Block('sections/subscriptions/notification.inc');
		$notification->message = $_POST['message'];
		$notification->documents = $documents;
		$notification->section = $section;
		$email->blocks[] = $notification;
		$message = $email->render();

		$errorCount = 0;
		foreach($section->getSubscriptions() as $subscription)
		{
			try { $subscription->notify($message); }
			catch (Exception $e) { $errorCount++; }
		}
		if ($errorCount) { $_SESSION['errorMessages'][] = new Exception('sections/subscriptions/badEmailAddresses'); }

		$template = new Template();
		$success = new Block('sections/subscriptions/notificationSuccess.inc');
		$success->message = $message;
		$template->blocks[] = $success;
		echo $template->render();
	}
	else
	{
		$form = new Block('sections/subscriptions/notificationForm.inc');
		$form->section = $section;
		$form->return_url = $_REQUEST['return_url'];

		$template = new Template();
		$template->blocks[] = $form;
		echo $template->render();
	}
}
else
{
	$_SESSION['errorMessages'][] = new Exception('noAccessAllowed');
	Header("Location: $_REQUEST[return_url]");
}
*/