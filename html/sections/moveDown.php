<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET sectionNode_id
 */
	verifyUser(array('Administrator','Webmaster'));

	$sectionNode = new SectionNode($_GET['sectionNode_id']);

	try { $sectionNode->moveDown(); }
	catch (Exception $e) { $_SESSION['errorMessages'][] = $e; }

	Header('Location: home.php');
?>