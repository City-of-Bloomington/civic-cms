<?php
/**
 * @copyright Copyright (C) 2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
if (isset($_POST['email']))
{
	if ($_POST['password'] && $_POST['retype'] && ($_POST['password']===$_POST['retype']))
	{
		$account = new PendingUser();
		$account->setEmail($_POST['email']);
		$account->setPassword($_POST['password']);
		try
		{
			$email = new Template('email','text');
			$instructions = new Block('users/pending/activationInstructions.inc');
			$instructions->pendingUser = $account;
			$email->blocks[] = $instructions;

			$account->notify($email->render());

			$account->save();
			Header('Location: view.php?email='.$account->getEmail());
			exit();
		}
		catch (Exception $e)
		{
			# This is the error code MySQL throws on a Duplicate Key Insert
			if ($e->getCode() == 23000)
			{
				$_SESSION['errorMessages'][] = new Exception('users/pending/userAlreadyPending');
				Header('Location: view.php?email='.$account->getEmail());
				exit();
			}
			elseif($e->getMessage() == 'Unable to send mail')
			{
				$_SESSION['errorMessages'][] = new Exception('users/pending/invalidEmail');
			}
			else
			{
				$_SESSION['errorMessages'][] = $e;
			}
		}
	}
	else { $_SESSION['errorMessages'][] = new Exception('users/pending/passwordsDoNotMatch'); }

}

$template = new Template();
$template->blocks[] = new Block('users/pending/createAccountForm.inc');
echo $template->render();
