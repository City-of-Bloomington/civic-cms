#!/usr/local/bin/php
<?php
/**
 * Script to update alerts from the National Weather Service
 *
 * Add this script to your CRON system to update the content manager
 * with alerts from the National Weather Service.
 * The National Weather Service updates their system every 2 minutes;
 * adjust your CRON settings accordingly.  For our website, we run
 * this script every 5 minutes.
 *
 * @copyright 2008-2009 City of Bloomington, Indiana
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
include dirname(__FILE__).'/../configuration.inc';

$c = 0;
$events = array();
$alerts = simplexml_load_file(NATIONAL_WEATHER_SERVICE_FEED);
foreach($alerts->entry as $entry) {

	// Grab just the first line of the title
	preg_match('/^.*$/m',trim($entry->title),$matches);
	$title = $matches[0];

	foreach ($ALERT_IGNORE as $ignore) {
		if (preg_match($ignore,$title)) { continue 2; }
	}

	$capInfo = $entry->children('urn:oasis:names:tc:emergency:cap:1.1');
	if (count($capInfo)) {

		$events[] = $title;

		$alert = new Alert($title);
		$alert->setAlertType(new AlertType('Weather'));
		$alert->setStartTime($capInfo->effective);
		$alert->setEndTime($capInfo->expires);
		$alert->setText($entry->summary);
		$alert->setURL($entry->link['href']);
		print_r($alert);
		$alert->save();

		$c++;
	}
}
// Clean out weather alerts that the National Weather Service is no longer broadcasting
$list = new AlertList(array('alertType'=>'Weather'));
foreach ($list as $alert) {
	if (!in_array($alert->getTitle(),$events)) {
		$alert->delete();
	}
}

echo $alerts->asXML();
echo date('Y-m-d H:i:sp')." Added $c alerts\n";
