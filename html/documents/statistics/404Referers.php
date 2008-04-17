<?php
/**
 * @copyright Copyright (C) 2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET path
 */
$template = new Template('popup');

$referers = FileNotFoundLog::getReferers($_GET['path']);
$template->blocks[] = new Block('documents/statistics/404Referers.inc',array('referers'=>$referers));
echo $template->render();
