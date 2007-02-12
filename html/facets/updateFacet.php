<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
	verifyUser('Webmaster');

	if (isset($_GET['facet_id'])) { $facet = new Facet($_GET['facet_id']); }
	if (isset($_POST['facet_id']))
	{
		$facet = new Facet($_POST['facet_id']);
		$facet->setName($_POST['facet']['name']);

		try
		{
			$facet->save();
			Header("Location: home.php");
			exit();
		}
		catch (Exception $e) { $_SESSION['errorMessages'][] = $e; }
	}

	$template = new Template('backend');
	$template->blocks[] = new Block('facets/updateFacetForm.inc',array('facet'=>$facet));
	$template->render();
?>