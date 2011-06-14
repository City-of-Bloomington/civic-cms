<?php
/**
 * @copyright Copyright (C) 2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET alert_id
 */
verifyUser(array('Administrator','Webmaster'));

$alert = new Alert($_GET['alert_id']);
$alert->delete();

Header('Location: '.BASE_URL.'/alerts');
