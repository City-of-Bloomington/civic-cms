<?php
/**
 *	Logs a user into the system.
 *
 *	A logged in user will have a $_SESSION['USER']
 *								$_SESSION['IP_ADDRESS']
 *
 * @copyright 2006-2009 City of Bloomington, Indiana
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param POST username
 * @param POST password
 */
if (isset($_REQUEST['username']) && isset($_REQUEST['password'])) {
	try {
		$user = new User($_POST['username']);
		$user->authenticate($_POST['password']);
		$user->startNewSession();
	}
	catch (Exception $e) {
		$_SESSION['errorMessages'][] = $e;
		header('Location: '.BASE_URL.'/login');
		exit();
	}

	if (userHasRole(array('Administrator','Webmaster','Content Creator'))) {
		header('Location: '.BASE_URL.'/documents');
	}
	else {
		header('Location: '.BASE_URL.'/sections/subscriptions');
	}
}
else {
	$_SESSION['errorMessages'][] = new Exception('invalidLogin');
	header('Location: '.BASE_URL.'/login');
	exit();
}
