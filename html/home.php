<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
 	$template = new Template();
 	$document = new Document(1);
 	$template->document = $document;
	$template->blocks[] = new Block("documents/viewDocument.inc",array('document'=>$document));
 	$template->render();
?>