<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
/*
	$_GET variables:	category_id
*/
	$template = new Template();
	$category = new Category($_GET['category_id']);
	$template->blocks[] = new Block("categories/viewCategory.inc",array('category'=>$category));
	$template->blocks[] = new Block("categories/documents.inc",array('category'=>$category));
	$template->render();
?>
