<?php
/**
 * @copyright Copyright (C) 2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET section_id
 * @param GET return_url
 */
verifyUser();

$section = new Section($_REQUEST['section_id']);

if ($section->permitsPostingBy($_SESSION['USER']))
{
	if (isset($_POST['message']))
	{
		foreach($section->getSubscriptions() as $subscription)
		{
			$documents = array();
			foreach($_POST['documents'] as $id=>$checked)
			{
				$documents[] = new Document($id);
			}

			$email = new Template('email','text');
			$message = new Block('sections/subscriptions/notification.inc');
			$message->message = $_POST['message'];
			$message->documents = $documents;
			$email->blocks[] = $message;

			$subscription->notify($email->render());
		}
		Header("Location: $_REQUEST[return_url]");
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
