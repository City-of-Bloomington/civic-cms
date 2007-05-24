<?php
/**
 * @copyright Copyright (C) 2006 Cliff Ingham. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Document $this->document
 */
?>
<div id="leftSidebar" class="left sidebar">
	<?php
		$panel = new Panel('leftSidebar');
		$widgets = isset($this->document) ? $panel->getWidgets($this->document) : $panel->getWidgets();

		foreach($widgets as $widget) { $widget->render($this); }

		if (isset($_SESSION['USER']))
		{
			echo '<div><div class="titleBar">Admin</div>';
			# Show all these sidebar boxes, if the user's someone in the system
			if (userHasRole('Administrator')) { include APPLICATION_HOME.'/includes/sidebarBoxes/Administrator.inc'; }
			if (userHasRole('Webmaster')) { include APPLICATION_HOME.'/includes/sidebarBoxes/Webmaster.inc'; }
			if (userHasRole('Content Creator')) { include APPLICATION_HOME.'/includes/sidebarBoxes/ContentCreator.inc'; }
			echo '</div>';
		}
	?>
</div>
