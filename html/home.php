<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
 	$template = new Template('blank');
 	$template->document = new Document(1);
	$template->blocks[] = new Block('documents/viewDocument.inc',array('document'=>$template->document));
 	$template->render();
?>