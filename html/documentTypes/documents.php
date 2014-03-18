<?php
/**
 * @copyright 2007-2014 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET documentType_id
 * @param GET facetGroup_id
 *
 * Displays the documents of a given DocumentType, organized by Facet
 */
$search = ['active'=>date('Y-m-d')];

if (!empty($_GET['documentType_id'])) {
	try { $type = new DocumentType($_GET['documentType_id']); }
	catch (Exception $e) {
		$_SESSION['errorMessages'][] = $e;
		Header('Location: home.php');
		exit();
	}
	$search['documentType_id'] = $type->getId();

	$facetGroup = null;
	if (!empty($_GET['facetGroup_id'])) {
		try {
			$facetGroup = new FacetGroup($_GET['facetGroup_id']);
		}
		catch (Exception $e) {
			// Just ignore the unknown facetGroup
		}
	}
	if (!$facetGroup) {
		// Load the default Facet Group
		if ($type->getDefaultFacetGroup_id()) { $facetGroup = $type->getDefaultFacetGroup(); }
	}
	if ($facetGroup) { $search['facetGroup_id'] = $facetGroup->getId(); }


	$facet = null;
	if (!empty($_GET['facet_id'])) {
		try {
			$facet = new Facet($_GET['facet_id']);
			$search['facet_id'] = $facet->getId();
		}
		catch (Exception $e) {
			// Just ignore invalid facets
		}
	}


	$template = (isset($_GET['format'])) ? new Template('default',$_GET['format']) : new Template();
	if ($template->outputFormat=='html') {
		$template->blocks[] = new Block('documentTypes/breadcrumbs.inc', ['documentType'=>$type]);
		$template->blocks[] = new Block('documentTypes/facetGroupTabs.inc', ['documentType'=>$type, 'facetGroup'=>$facetGroup]);
		if ($facetGroup) {
			$template->blocks[] = new Block('documentTypes/facetTabs.inc', ['facetGroup'=>$facetGroup, 'facet'=>$facet]);
		}
	}

	$documents = new DocumentList();
	$documents->find($search, $type->getOrdering());
	$paginator = $documents->getPagination(20);
	$page = !empty($_GET['page']) ? (int)$_GET['page'] : 1;
	$paginator->setCurrentPageNumber($page);

	$template->blocks[] = new Block('documentTypes/documents.inc', ['documents'=>$paginator, 'documentType'=>$type]);

	if ($template->outputFormat == 'html') {
		$template->blocks[] = new Block('pageNavigation.inc', ['paginator'=>$paginator]);
	}

	echo $template->render();
}
else {
	header('Location: '.BASE_URL);
	exit();
}
