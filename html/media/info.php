<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET media_id
 */
	verifyUser();
	$media = new Media($_GET['media_id']);

	$template = new Template('backend');
	$template->blocks[] = new Block('media/info.inc',array('media'=>$media));
	echo $template->render();
?>
