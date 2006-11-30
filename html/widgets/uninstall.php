<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
	verifyUser("Administrator");

	$widget = Widget::load($_GET['widget']);
	try { $widget->uninstall(); }
	catch (Exception $e) { $_SESSION['errorMessages'][] = $e; }

	Header("Location: home.php");
?>