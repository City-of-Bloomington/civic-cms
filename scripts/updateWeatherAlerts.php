#!/usr/local/bin/php
<?php
/**
 * @copyright Copyright (C) 2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * This is a shell script intended for CRON.
 *
 * Add this script to your CRON system to update the content manager
 * with alerts from the National Weather Service.
 * The National Weather Service updates their system every 2 minutes;
 * adjust your CRON settings accordingly.  For our website, we run
 * this script every 5 minutes.
 */
include '/var/www/sites/content_manager/configuration.inc';
$c = 0;
$alerts = simplexml_load_file(NATIONAL_WEATHER_SERVICE_CAP_FILE);
foreach($alerts->children('http://www.incident.com/cap/1.0') as $info)
{
	foreach($ALERT_COUNTIES as $county)
	{
		if (preg_match($county,$info->area->areaDesc))
		{
			foreach($ALERT_IGNORE as $ignore)
			{
				if (preg_match($ignore,$info->event)) { break 2; }
			}

			$alert = new Alert($info->event);
			$alert->setAlertType(new AlertType('Weather'));
			$alert->setStartTime($info->effective);
			$alert->setEndTime($info->expires);
			$alert->setText($info->description);
			$alert->setURL($info->web);
			$alert->save();

			$c++;
		}
	}
}
echo $alerts->asXML();
echo date('Y-m-d H:i:sp')." Added $c alerts\n";
