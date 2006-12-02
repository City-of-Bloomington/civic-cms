<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
/*
	$_GET variables:	section_id
*/
	$template = new Template();

	$section = new Section($_GET['section_id']);
	$template->widgets = $section->getWidgets();
	$template->document = $section->getDocument();

	$template->blocks[] = new Block("sections/viewSection.inc",array('section'=>$section));
	$template->blocks[] = new Block("breadcrumbs.inc",array('section'=>$section));
	if (userHasRole("Content Creator") && $_SESSION['USER']->getDepartment_id()==$section->getDocument()->getDepartment_id())
	{
		$toolbar = new Block("documents/toolbar.inc");
		$toolbar->document = $section->getDocument();
		$toolbar->section = $section;
		$template->blocks[] = $toolbar;
	}
	$template->blocks[] = new Block("documents/viewDocument.inc",array('document'=>$section->getDocument()));
	$template->blocks[] = new Block("sections/subsections.inc",array('section'=>$section));

	$template->render();
?>