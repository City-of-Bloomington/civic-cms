<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET facet_id
 */
	verifyUser(array('Administrator','Webmaster'));

	$facet = new Facet($_GET['facet_id']);
	$facet->delete();

	Header('Location: home.php');
?>