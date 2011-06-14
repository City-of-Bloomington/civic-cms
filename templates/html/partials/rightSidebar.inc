<?php
/**
 * @copyright 2006-2010 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Document $this->document
 */
?>
<div id="rightSidebar" class="right sidebar">
	<?php
		if (isset($this->document)) {
			include APPLICATION_HOME.'/templates/html/partials/pageTools.inc';
		}

		$panel = new Panel('rightSidebar');
		$widgets = isset($this->document)
				? $panel->getWidgets($this->document)
				: $panel->getWidgets();
		foreach($widgets as $widget) {
			$widget->render($this);
		}
	?>
</div>
