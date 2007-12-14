<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET type
 * @param GET url
 */
	$template = new Template();
	$template->blocks[] = new Block('feeds/breadcrumbs.inc');

	if (isset($_GET['url']))
	{
		$url = new URL($_GET['url']);
		$handler = new Block('feeds/handler.inc');
		$handler->url = new URL($_GET['url']);
		$handler->type = $_GET['type'];
		$template->blocks[] = $handler;
	}

	$template->blocks[] = new Block('feeds/rss.inc');
	$template->blocks[] = new Block('feeds/ical.inc');
	$template->blocks[] = new Block('feeds/kml.inc');
	$template->render();
