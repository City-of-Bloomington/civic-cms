<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET widget_id
 */
	verifyUser(array('Administrator','Webmaster'));

	$widget = new WidgetInstallation($_GET['widget_id']);
	$widget->delete();

	Header('Location: home.php');
?>