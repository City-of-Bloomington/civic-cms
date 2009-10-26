<?php
/**
 * @copyright 2006-2009 City of Bloomington, Indiana
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
$template = new Template();
$template->blocks[] = new Block('facets/breadcrumbs.inc');

$groups = new FacetGroupList();
$groups->find();

$template->blocks[] = new Block('facets/facetGroupList.inc',array('facetGroupList'=>$groups));

echo $template->render();
