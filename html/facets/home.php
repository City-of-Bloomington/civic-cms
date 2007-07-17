<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
	verifyUser(array('Administrator','Webmaster'));


	$template = new Template();
	$template->blocks[] = new Block('facets/info.inc');

	$groups = new FacetGroupList();
	$groups->find();
	foreach($groups as $group)
	{
		$template->blocks[] = new Block('facets/facetList.inc',array('facetList'=>$group->getFacets(),'title'=>$group->getName(),'facetGroup'=>$group));
	}

	$template->blocks[] = new Block('facets/facetGroupList.inc',array('facetGroupList'=>$groups));

	$template->render();
?>