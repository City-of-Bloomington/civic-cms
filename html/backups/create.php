<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
	verifyUser('Administrator');

	$backup = new Backup();

	try { $backup->save(); }
	catch (Exception $e) { $_SESSION['errorMessages'][] = $e; }

	Header('Location: home.php');
?>