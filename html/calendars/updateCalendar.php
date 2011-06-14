<?php
/**
 * @copyright Copyright 2006-2010 City of Bloomington, Indiana
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
verifyUser(array('Administrator','Webmaster'));

if (isset($_REQUEST['calendar_id'])) {
	try {
		$calendar = new Calendar($_GET['calendar_id']);
	}
	catch (Exception $e) {
		header('Location: '.BASE_URL.'/calendars');
		exit();
	}
}
if (isset($_POST['calendar'])) {
	foreach($_POST['calendar'] as $field=>$value) {
		$set = 'set'.ucfirst($field);
		$calendar->$set($value);
	}

	try {
		$calendar->save();
		header('Location: home.php?calendar_id='.$calendar->getId());
		exit();
	}
	catch (Exception $e) { $_SESSION['errorMessages'][] = $e; }
}

$template = new Template();
$template->blocks[] = new Block('calendars/updateCalendarForm.inc',array('calendar'=>$calendar));
echo $template->render();
