<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
$template = new Template('backend');

$hits = DocumentAccessLog::getTopDocuments();
$template->blocks[] = new Block('documents/statistics/topHits.inc',array('hits'=>$hits));

$hits = SearchLog::getTopSearches();
$template->blocks[] = new Block('search/statistics/topSearches.inc',array('searches'=>$hits));

$hits = FileNotFoundLog::getTopRequests();
$template->blocks[] = new Block('documents/statistics/top404.inc',array('requests'=>$hits));

$template->blocks[] = new Block('documents/statistics/departmentTopHits.inc');

echo $template->render();
