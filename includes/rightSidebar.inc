<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
?>
<div class="right sidebar">
<?php
	if (isset($this->document))
	{
		include APPLICATION_HOME.'/includes/sidebarBoxes/attachments.inc';
		foreach($this->document->getWidgets() as $widget) { $widget->render(); }
	}
	include APPLICATION_HOME.'/includes/sidebarBoxes/Facets.inc';
?>
</div>
