<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
	verifyUser(array('Administrator','Webmaster'));

	if (isset($_POST['facetGroup']))
	{
		$facetGroup = new FacetGroup();
		foreach($_POST['facetGroup'] as $field=>$value)
		{
			$set = 'set'.ucfirst($field);
			$facetGroup->$set($value);
		}

		try
		{
			$facetGroup->save();
			Header('Location: home.php');
			exit();
		}
		catch(Exception $e) { $_SESSION['errorMessages'][] = $e; }
	}

	$template = new Template();
	$template->blocks[] = new Block('facets/addFacetGroupForm.inc');
	echo $template->render();
?>