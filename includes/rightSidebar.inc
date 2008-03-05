<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Document $this->document
 */
?>
<div id="rightSidebar" class="right sidebar">
<?php
	if (isset($this->document)) { include APPLICATION_HOME.'/includes/pageTools.inc'; }


	$panel = new Panel('rightSidebar');
	$widgets = isset($this->document) ? $panel->getWidgets($this->document) : $panel->getWidgets();

	foreach($widgets as $widget) { $widget->render($this); }
?>
</div>
