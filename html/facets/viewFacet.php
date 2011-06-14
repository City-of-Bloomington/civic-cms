<?php
/**
 * @copyright 2007-2009 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET facet_id
 */
if (isset($_GET['facet_id']) && $_GET['facet_id']) {
	try {
		$facet = new Facet($_GET['facet_id']);
	}
	catch(Exception $e) {
		$_SESSION['errorMessages'][] = $e;
	}
}

if (isset($facet)) {
	$template = new Template();
	$template->blocks[] = new Block('facets/breadcrumbs.inc',array('facet'=>$facet));
	$template->blocks[] = new Block('facets/relatedItems.inc',array('facet'=>$facet));

	echo $template->render();
}
else {
	header('Location: '.BASE_URL.'/facets');
}
