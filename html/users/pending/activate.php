<?php
/**
 * @copyright Copyright (C) 2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET hash
 */
$template = new Template();
if (isset($_GET['hash']))
{
	try
	{
		$pendingAccount = new PendingUser($_GET['hash']);
		$user = $pendingAccount->activate();
		$template->blocks[] = new Block('users/pending/activated.inc');
		$template->blocks[] = new Block('loginForm.inc');
	}
	catch(Exception $e)
	{
		$_SESSION['errorMessages'][] = $e;
		$template->blocks[] = new Block('users/pending/createAccountForm.inc');
	}
}
$template->render();
