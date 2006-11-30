<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
	verifyUser("Administrator");

	$template = new Template();
	$template->blocks[] = new Block("widgets/widgetList.inc",array('widgetList'=>Widget::findAll()));
	$template->render();
?>