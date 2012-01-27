<?php
/**
 * @copyright 2007-2012 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET media_id
 */
verifyUser();

try  {
	$media = new Media($_GET['media_id']);
}
catch (Exception $e) {
	header('http/1.1 404 Not Found');
	header('Status: 404 Not Found');
	$_SESSION['errorMessages'][] = $e;
}

$template = new Template('backend');
if (isset($media)) {
	$template->blocks[] = new Block('media/info.inc',array('media'=>$media));
}
echo $template->render();
