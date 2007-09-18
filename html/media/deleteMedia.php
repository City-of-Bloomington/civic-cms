<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET media_id
 */
	verifyUser();

	$media = new Media($_GET['media_id']);
	if ($media->permitsEditingBy($_SESSION['USER']))
	{
		$media->delete();
	}
	else { $_SESSION['errorMessages'][] = new Exception('noAccessAllowed'); }

	Header('Location: '.BASE_URL.'/media');
?>