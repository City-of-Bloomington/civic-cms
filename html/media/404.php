<?php
/**
 * @copyright 2008-2011 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
if (preg_match('|/([a-z]+)/([0-9]+)\.[a-z]{3}$|',$_SERVER['REQUEST_URI'],$matches)) {
	if (in_array($matches[1],array_keys(Image::getSizes()))) {
		$_GET['size'] = $matches[1];
	}
	$_GET['media_id'] = $matches[2];

	try {
		$media = new Media($_GET['media_id']);
	}
	catch (Exception $e) {
		$_SESSION['errorMessages'][] = $e;
	}

	include APPLICATION_HOME.'/html/media/media.php';
}
else {
	header('http/1.1 404 Not Found');
	header('Status: 404 Not Found');
	$_SESSION['errorMessages'][] = new Exception('media/unknownMedia');
}

$template = new Template();
echo $template->render();
