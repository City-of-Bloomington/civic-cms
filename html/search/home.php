<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET search
 * @param GET type Document, Event
 */
$template = new Template();
$template->blocks[] = new Block('search/searchForm.inc',array('search'=>$_GET['search']));

if (isset($_GET['search']) && $_GET['search'])
{
	try
	{
		$search = new Search();
		$results = $search->find($_GET['search']);

		$resultBlock = new Block('search/results.inc');
		$resultBlock->results = $results;
		if (isset($_GET['type'])) { $resultBlock->currentType = $_GET['type']; }

		$template->blocks[] = $resultBlock;
	}
	catch (Exception $e) { exception_handler($e); }
}
$template->render();
