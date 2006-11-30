<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
 	$template = new Template();
	$template->blocks[] = new Block("documents/viewDocument.inc",array('document'=>new Document(1)));
 	$template->render();
?>