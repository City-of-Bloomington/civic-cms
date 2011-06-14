<?php
/**
 * @copyright 2007-2009 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET facetGroup_id
 */
verifyUser(array('Administrator','Webmaster'));

$facetGroup = new FacetGroup($_REQUEST['facetGroup_id']);
if (isset($_POST['facetGroup'])) {
	foreach ($_POST['facetGroup'] as $field=>$value) {
		$set = 'set'.ucfirst($field);
		$facetGroup->$set($value);
	}
	$facetGroup->setDescription($_POST['description']);

	try {
		$facetGroup->save();
		header('Location: '.$facetGroup->getURL());
		exit();
	}
	catch (Exception $e) {
		$_SESSION['errorMessages'][] = $e;
	}
}

$template = new Template();
$template->blocks[] = new Block('facets/updateFacetGroupForm.inc',array('facetGroup'=>$facetGroup));
echo $template->render();
