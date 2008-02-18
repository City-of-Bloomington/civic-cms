<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET facetGroup_id
 */
	verifyUser(array('Administrator','Webmaster'));

	if (isset($_GET['facetGroup_id'])) { $facetGroup = new FacetGroup($_GET['facetGroup_id']); }
	if (isset($_POST['facetGroup_id']))
	{
		$facetGroup = new FacetGroup($_POST['facetGroup_id']);
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
		catch (Exception $e) { $_SESSION['errorMessages'][] = $e; }
	}

	$template = new Template();
	$template->blocks[] = new Block('facets/updateFacetGroupForm.inc',array('facetGroup'=>$facetGroup));
	echo $template->render();
?>