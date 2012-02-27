<?php
/**
 *	Logs a user into the system using CAS
 *
 * @copyright 2006-2012 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
if (isset($_REQUEST['return_url'])) {
	$_SESSION['return_url'] = $_REQUEST['return_url'];
}

$return_url = isset($_SESSION['return_url']) ? $_SESSION['return_url'] : BASE_URL;

// If they don't have CAS configured, send them onto the application's
// internal authentication system
if (!defined('CAS')) {
	header('Location: '.BASE_URL.'/login/login?return_url='.$return_url);
	exit();
}

require_once CAS.'/CAS.php';
phpCAS::client(CAS_VERSION_2_0, CAS_SERVER, 443, CAS_URI, false);
phpCAS::setNoCasServerValidation();
phpCAS::forceAuthentication();

try {
	$user = new User(phpCAS::getUser());
	$user->startNewSession();
}
catch (Exception $e) {
	$_SESSION['errorMessages'][] = $e;
}

header("Location: $return_url");
