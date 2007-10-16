<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param char SESSION[LANGUAGE]
 */
	$list = new DocumentList(array('lang'=>$_SESSION['LANGUAGE']));
	$template = new Template();
	$template->blocks[] = new Block('languages/documentList.inc',array('documentList'=>$list));
	$template->render();
?>
