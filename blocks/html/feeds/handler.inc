<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param string $this->type
 * @param URL $this->url
 *
 * Since some feed types aren't handled natively by most browsers,
 * we can't just create links throughout the site and expect it to
 * work for folks.  Rather, we can link to this page, and it will
 * draw the appropriate URL so users can copy and paste it into
 * whatever application they want to use for that type of feed
 */
	switch ($this->type)
	{
		case 'webcal':
			$this->url->setScheme('webcal');
			$title = 'Custom Calendar';
			$message = 'Subscribe to this calendar by copying this URL into your calendar application';
			break;

		case 'rss':
			$title = 'Custom RSS Feed';
			$message = 'Subscribe to this feed by pointing your newsreader to this URL.';
			break;

		case 'kml':
			$title = 'Custom KML Feed';
			$message = 'You can import this KML URL into Google Earth or Google Maps';
			break;

		default:
	}
	echo <<<EOT
	<h2>$title</h2>
	<p>$message</p>
	<p><a href="{$this->url}">{$this->url}</a></p>
EOT;
