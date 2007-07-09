<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET media_id
 */
	$image = new Image($_GET['media_id']);

	Header('Content-type: '.$image->getMime_type());
	readfile("{$image->getDirectory()}/{$image->getFilename()}");
?>