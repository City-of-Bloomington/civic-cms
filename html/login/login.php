<?php
/**
 * @copyright Copyright (C) 2006,2007,2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param POST username
 * @param POST password
 *	Logs a user into the system.
 *	A logged in user will have a $_SESSION['USER']
 *								$_SESSION['IP_ADDRESS']
 *								$_SESSION['APPLICATION_NAME']
 */
try
{
	$user = new User($_POST['username']);
	$user->authenticate($_POST['password']);
	$user->startNewSession();
}
catch (Exception $e)
{
	$_SESSION['errorMessages'][] = $e;
	Header('Location: '.BASE_URL.'/login');
	exit();
}

if (userHasRole(array('Administrator','Webmaster','Content Creator')))
{
	Header('Location: '.BASE_URL.'/documents');
}
else
{
	Header('Location: '.BASE_URL.'/sections/subscriptions');
}
