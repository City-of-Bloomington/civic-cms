<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET facet_id
 */
	$facet = new Facet($_GET['facet_id']);

	$template = new Template();
	$template->blocks[] = new Block('facets/facetInfo.inc',array('facet'=>$facet));

	$list = $facet->getRelatedFacets();
	foreach($list as $f)
	{
		$template->blocks[] = new Block('facets/facetDocuments.inc',array('facet'=>$f));
	}

	$template->render();
?>