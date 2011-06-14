<?php
/**
 * @copyright Copyright (C) 2006 Cliff Ingham. All rights reserved.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Document $this->document
 */
?>
<div id="leftSidebar" class="left sidebar">
	<?php
		$panel = new Panel('leftSidebar');
		$widgets = isset($this->document) ? $panel->getWidgets($this->document) : $panel->getWidgets();

		foreach($widgets as $widget) { $widget->render($this); }
	?>
</div>
