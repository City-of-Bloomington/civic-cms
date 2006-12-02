<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
 	$template = new Template('blank');
 	$loginForm = new Block("loginForm.inc",array('response'=>new URL($_GET['return'])));
 	$template->blocks[] = $loginForm;
 	$template->render();
?>