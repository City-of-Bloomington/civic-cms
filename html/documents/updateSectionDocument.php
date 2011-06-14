<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET sectionDocument_id
 * @param GET featured
 * This script is currently only accessed by an AJAX call.  It should not send any output
 */
	verifyUser();
	$sectionDocument = new SectionDocument($_GET['sectionDocument_id']);
	if ($sectionDocument->getDocument()->permitsEditingBy($_SESSION['USER']))
	{
		$sectionDocument->setFeatured($_GET['featured']);
		try { $sectionDocument->save(); }
		catch(Exception $e) { $_SESSION['errorMessages'][] = $e; }
	}
