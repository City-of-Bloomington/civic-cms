<?php
/**
 * @copyright 2009 City of Bloomington, Indiana
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET facetGroup_id
 */
$facetGroup = new FacetGroup($_GET['facetGroup_id']);

$template = new Template();
$template->blocks[] = new Block('facets/breadcrumbs.inc');

$facets = new Block('facets/facetList.inc');
$facets->facetList = $facetGroup->getFacets();
$facets->title = $facetGroup->getName();
$facet->group = $facetGroup;
$template->blocks[] = $facets;

echo $template->render();

