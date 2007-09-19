<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
	$template = new Template();
	$template->blocks[] = new Block('tags/info.inc');

	$groups = new TagGroupList();
	$groups->find();
	foreach($groups as $group)
	{
		$template->blocks[] = new Block('tags/tagList.inc',array('tagList'=>$group->getTags(),'title'=>$group->getName(),'tagGroup'=>$group));
	}

	if (userHasRole(array('Administrator','Webmaster')))
	{
		$template->blocks[] = new Block('tags/tagGroupList.inc',array('tagGroupList'=>$groups));
	}

	$template->render();
?>
