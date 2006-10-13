<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
	verifyUser("Administrator");

	$template = new Template();
	$template->blocks[] = new Block("sections/listSections.inc",array('sectionList'=>new SectionList(array("parent_id"=>1))));
	$template->render();
?>