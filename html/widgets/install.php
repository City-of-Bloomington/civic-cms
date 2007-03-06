<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
	verifyUser('Administrator');

	$widget = Widget::load($_GET['widget']);
	try { $widget->install(); }
	catch (Exception $e) { $_SESSION['errorMessages'][] = $e; }

	Header('Location: home.php');
?>