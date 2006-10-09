<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
	verifyUser("Administrator");

	$template = new Template();
	$template->blocks[] = new Block("categories/listCategories.inc",array('categoryList'=>new CategoryList(array("parent_id"=>1))));
	$template->render();
?>