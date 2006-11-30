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

	$template->blocks[] = new Block("sections/viewSection.inc",array('section'=>$section));
	$template->blocks[] = new Block("documents/viewDocument.inc",array('document'=>$section->getDocument()));
	$template->blocks[] = new Block("sections/documents.inc",array('section'=>$section));

	$template->render();
?>