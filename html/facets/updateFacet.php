<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET facet_id
 */
	verifyUser(array('Administrator','Webmaster'));

	if (isset($_GET['facet_id'])) { $facet = new Facet($_GET['facet_id']); }
	if (isset($_POST['facet_id']))
	{
		$facet = new Facet($_POST['facet_id']);
		foreach($_POST['facet'] as $field=>$value)
		{
			$set = 'set'.ucfirst($field);
			$facet->$set($value);
		}
		$facet->setDescription($_POST['description']);

		try
		{
			$facet->save();
			Header("Location: home.php");
			exit();
		}
		catch (Exception $e) { $_SESSION['errorMessages'][] = $e; }
	}

	$template = new Template();
	$template->blocks[] = new Block('facets/updateFacetForm.inc',array('facet'=>$facet));
	echo $template->render();
