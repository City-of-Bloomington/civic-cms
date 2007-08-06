<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET category
 */
	$template = new Template();
	$template->blocks[] = new Block('directory/breadcrumbs.inc',array('category'=>$_GET['category']));
	$template->blocks[] = new Block('directory/viewCategory.inc',array('category'=>$_GET['category']));
	$template->render();
?>