<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
	verifyUser(array('Administrator','Webmaster'));

	$template = new Template();

	$widgets = new WidgetInstallationList();
	$widgets->find();

	$template->blocks[] = new Block('widgets/widgetList.inc',array('widgetInstallationList'=>$widgets));

	echo $template->render();
?>