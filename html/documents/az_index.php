<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET letter
 */
	$letter = isset($_GET['letter']) ? substr($_GET['letter'],0,1) : 'A';

	$template = new Template();
	$template->blocks[] = new Block('documents/index.inc',array('letter'=>$letter));
	$template->render();
?>