<?php
/**
 * @copyright Copyright (C) 2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET email
 */
# This is disabled for now
Header('Location: '.BASE_URL);
/*
try
{
	$pending = new PendingUser($_GET['email']);
}
catch (Exception $e)
{
	$_SESSION['errorMessages'][] = $e;
	Header('Location: create.php');
	exit();
}

$template = new Template();
$template->blocks[] = new Block('users/pending/view.inc',array('pendingUser'=>$pending));
echo $template->render();
*/
