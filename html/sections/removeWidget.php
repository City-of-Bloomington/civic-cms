<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET sectionWidget_id
 */
	verifyUser(array('Administrator','Webmaster'));

	$widget = new SectionWidget($_GET['sectionWidget_id']);
	$section_id = $widget->getSection_id();

	$widget->delete();

	Header("Location: updateWidgets.php?section_id=$section_id");
?>