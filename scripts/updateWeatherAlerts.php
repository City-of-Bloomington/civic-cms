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
 * @copyright 2008-2017 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 */
include dirname(__FILE__).'/../configuration.inc';

$c = 0;
$events = [];

$request = curl_init(NATIONAL_WEATHER_SERVICE_FEED);
curl_setopt($request, CURLOPT_RETURNTRANSFER,true);
curl_setopt($request, CURLOPT_FOLLOWLOCATION, true);
curl_setopt($request, CURLOPT_USERAGENT, CMS_USER_AGENT);
$xml = curl_exec($request);
echo "$xml\n";

if ($xml) {
	$alerts = simplexml_load_string($xml);
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
			echo "Adding: $title\n";

			$alert = new Alert($title);
			$alert->setAlertType(new AlertType('Weather'));
			$alert->setStartTime($capInfo->effective);
			$alert->setEndTime($capInfo->expires);
			$alert->setText($entry->summary);
			$alert->setURL($entry->link['href']);
			$alert->save();

			$c++;
		}
	}
}
else {
    echo curl_error($request);
}
echo date('Y-m-d H:i:sp')." Added $c alerts\n";

// Clean out weather alerts that the National Weather Service is no longer broadcasting
$c = 0;
$list = new AlertList(array('alertType'=>'Weather'));
foreach ($list as $alert) {
	if (!in_array($alert->getTitle(),$events)) {
		echo "Deleting: {$alert->getTitle()}\n";
		$alert->delete();
		$c++;
	}
}
echo date('Y-m-d H:i:sp')." Deleted $c alerts\n";
