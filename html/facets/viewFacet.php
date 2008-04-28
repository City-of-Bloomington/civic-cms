<?php
/**
 * @copyright Copyright (C) 2007-2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET facet_id
 */
if (isset($_GET['facet_id']) && $_GET['facet_id'])
{
	try { $facet = new Facet($_GET['facet_id']); }
	catch(Exception $e) { $_SESSION['errorMessages'][] = $e; }
}

if (isset($facet))
{
	$template = new Template();
	$template->blocks[] = new Block('facets/breadcrumbs.inc',array('facet'=>$facet));
	$template->blocks[] = new Block('facets/facetDocuments.inc',array('facet'=>$facet));

	echo $template->render();
}
else
{
	Header('Location: '.BASE_URL.'/facets');
}
