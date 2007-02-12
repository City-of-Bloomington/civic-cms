<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
	verifyUser('Webmaster');

	if (isset($_POST['facet']))
	{
		$facet = new Facet();
		$facet->setName($_POST['facet']['name']);

		try
		{
			$facet->save();
			Header("Location: home.php");
			exit();
		}
		catch(Exception $e) { $_SESSION['errorMessages'][] = $e; }
	}

	$template = new Template('backend');
	$template->blocks[] = new Block('facets/addFacetForm.inc');
	$template->render();
?>