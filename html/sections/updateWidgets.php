<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET section_id
 */
	verifyUser(array('Administrator','Webmaster'));

	$section = new Section($_GET['section_id']);

	$widgets = new SectionWidgetList(array('section_id'=>$section->getId()));

	$template = new Template();
	$template->blocks[] = new Block('sections/widgetList.inc',array('section'=>$section,'sectionWidgetList'=>$widgets));
	echo $template->render();
?>