<?php
/**
 * @copyright Copyright (C) 2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
verifyUser(array('Administrator','Webmaster'));

$alertList = new AlertList();
$alertList->find();

$template = new Template('backend');
$template->blocks[] = new Block('alerts/alertMaintenance.inc',array('alertList'=>$alertList));
echo $template->render();
