<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
	verifyUser("Webmaster");

	$template = new Template('backend');
	$template->blocks[] = new Block("sections/listSections.inc",array('section'=>new Section(1)));
	$template->render();
?>