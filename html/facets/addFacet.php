<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
	verifyUser(array('Administrator','Webmaster'));

	if (isset($_POST['facet']))
	{
		$facet = new Facet();
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
		catch(Exception $e) { $_SESSION['errorMessages'][] = $e; }
	}

	$template = new Template();
	$template->blocks[] = new Block('facets/addFacetForm.inc');
	echo $template->render();
