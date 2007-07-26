<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
	verifyUser(array('Administrator','Webmaster'));

	$template = new Template();
	$template->blocks[] = new Block("sections/listSections.inc",array('section'=>new Section(1)));

	$list = new SectionList(array('parent_id'=>'null'));
	$template->blocks[] = new Block('sections/unassignedSections.inc',array('sectionList'=>$list));
	$template->render();
?>