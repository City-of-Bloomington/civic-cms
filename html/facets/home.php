<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
	$facetList = new FacetList();
	$facetList->find();

	$template = new Template();
	$template->blocks[] = new Block('facets/facetList.inc',array('facetList'=>$facetList));
	$template->render();
?>