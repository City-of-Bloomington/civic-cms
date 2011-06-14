<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET location_id
 * @param GET return_url
 */
verifyUser();

$location = new Location($_GET['location_id']);

if ($location->permitsEditingBy($_SESSION['USER']))
{
	$location->delete();
}

Header("Location: $_GET[return_url]");
