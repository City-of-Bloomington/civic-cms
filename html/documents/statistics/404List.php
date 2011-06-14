<?php
/**
 * @copyright Copyright (C) 2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
verifyUser('Administrator');
$template = new Template('backend');

$requests = FileNotFoundLog::getTopRequests();
$template->blocks[] = new Block('documents/statistics/top404.inc',array('requests'=>$requests));
echo $template->render();
