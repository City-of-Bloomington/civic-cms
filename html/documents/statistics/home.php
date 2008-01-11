<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
$template = new Template('backend');

$hits = DocumentAccessLog::getTopDocuments();
$template->blocks[] = new Block('documents/statistics/topHits.inc',array('hits'=>$hits));

$template->render();
