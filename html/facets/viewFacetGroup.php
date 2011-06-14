<?php
/**
 * @copyright 2009 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET facetGroup_id
 */
$facetGroup = new FacetGroup($_GET['facetGroup_id']);

$template = new Template();
$template->blocks[] = new Block('facets/breadcrumbs.inc',array('facetGroup'=>$facetGroup));
$template->blocks[] = new Block('facets/facetGroupInfo.inc',array('facetGroup'=>$facetGroup));

$facets = new Block('facets/facetList.inc');
$facets->facetList = $facetGroup->getFacets();
$facets->title = $facetGroup->getName();
$facets->facetGroup = $facetGroup;
$template->blocks[] = $facets;

echo $template->render();

