<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET backup
 */
	verifyUser('Administrator');

	$backup = new Backup($_GET['backup']);

	Header("Pragma: public");
	Header('Content-type: application/x-gzip');
	Header("Content-Disposition: attachment; filename=$backup");
	Header("Content-length: {$backup->getFilesize()}");

	readfile("{$backup->getPath()}/{$backup->getFilename()}");
?>