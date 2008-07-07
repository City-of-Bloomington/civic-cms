<?php
/**
 * @copyright Copyright (C) 2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Document $this->document
 */
$panel = new Panel('alerts');
$widgets = isset($this->document) ? $panel->getWidgets($this->document) : $panel->getWidgets();
if (count($widgets))
{
	echo '<div id="alerts">';
	foreach($widgets as $widget) { $widget->render($this); }
	echo '</div>';
}
