<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET locationGroup_id
 */
	verifyUser(array('Webmaster','Administrator'));
	$locationGroup = new LocationGroup($_GET['locationGroup_id']);
	$locationGroup->delete();
	Header('Location: '.BASE_URL.'/locations');
