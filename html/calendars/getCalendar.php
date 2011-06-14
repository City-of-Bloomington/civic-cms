<?php
/**
 * Outputs the calendar in iCal format
 * 
 * @copyright Copyright 2006-2010 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
if (isset($_GET['calendar_id'])) {
	try {
		$calendar = new Calendar($_GET['calendar_id']);
	}
	catch (Exception $e) {
		$calendar = new Calendar();
	}
}
else {
	$calendar = new Calendar();
}

$template = new Template('ical',array('calendar'=>$calendar));
$template->blocks[] = new Block('calendars/ical.inc',array('calendar'=>$calendar));
echo $template->render();
