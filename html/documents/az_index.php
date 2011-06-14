<?php
/**
 * @copyright Copyright (C) 2007-2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET letter
 */
if (!isset($_GET['letterGroup'])) { $_GET['letterGroup'] = 'A,B,C'; }

$template = new Template();
$template->blocks[] = new Block('documents/index.inc',array('letterGroup'=>$_GET['letterGroup']));
echo $template->render();
