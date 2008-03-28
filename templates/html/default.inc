<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param string $this->title
 */
	if (!isset($this->title)) { $this->title = "City of Bloomington"; }
	include APPLICATION_HOME.'/includes/xhtmlStrictHeader.inc';
	include APPLICATION_HOME.'/includes/banner.inc';
	include APPLICATION_HOME.'/includes/menubar.inc';
?>
<div id="main-content-container">
	<?php
		include APPLICATION_HOME.'/includes/leftSidebar.inc';
		include APPLICATION_HOME.'/includes/rightSidebar.inc';
	?>
	<div id="mainContent" xml:lang="<?php echo $_SESSION['LANGUAGE']; ?>">
	<script type="text/javascript" src="<?php echo BASE_URL; ?>/js/lightbox/js/prototype.js"></script>
	<script type="text/javascript" src="<?php echo BASE_URL; ?>/js/lightbox/js/scriptaculous.js?load=effects,builder"></script>
	<script type="text/javascript" src="<?php echo BASE_URL; ?>/js/lightbox/js/lightbox.js"></script>
	<?php
		include FRAMEWORK.'/errorMessages.inc';

		echo $this->includeBlocks();

		$panel = new Panel('mainContent');
		$widgets = isset($this->document) ? $panel->getWidgets($this->document) : $panel->getWidgets();

		foreach($widgets as $widget) { $widget->render($this); }
	?>
	</div>
</div>
<?php
	include APPLICATION_HOME.'/includes/footer.inc';
	include FRAMEWORK.'/xhtmlFooter.inc';
?>
