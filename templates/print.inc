<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param string $this->title
 */
	if (!isset($this->title)) { $this->title = "City of Bloomington"; }
	$startTime = microtime(1);
?>
<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1//EN" "http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd">
<html xmlns="http://www.w3.org/1999/xhtml"
     xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
     xsi:schemaLocation="http://www.w3.org/MarkUp/SCHEMA/xhtml11.xsd"
     xml:lang="en" >
<head>
	<meta http-equiv="Content-Type" content="application/xhtml+xml; charset=utf-8" />
	<meta http-equiv="Content-Script-Type" content="text/javascript" />
	<link rel="SHORTCUT ICON" href="/favicon.ico" />
	<style type="text/css">
		@import url("<?php echo BASE_URL; ?>/skins/print.php");
	</style>
	<script type="text/javascript" src="<?php echo BASE_URL; ?>/js/functions.js"></script>
	<title><?php echo View::escape($this->title); ?></title>
</head>
<body>
<?php
	include APPLICATION_HOME.'/includes/banner.inc';
	include APPLICATION_HOME.'/includes/menubar.inc';
	include APPLICATION_HOME.'/includes/languages.inc';
	include APPLICATION_HOME.'/includes/leftSidebar.inc';
	include APPLICATION_HOME.'/includes/rightSidebar.inc';
?>
<div id="mainContent" lang="<?php echo $_SESSION['LANGUAGE']; ?>" xml:lang="<?php echo $_SESSION['LANGUAGE']; ?>">
	<?php
		include FRAMEWORK.'/errorMessages.inc';

		echo $this->includeBlocks();

		$panel = new Panel('mainContent');
		$widgets = isset($this->document) ? $panel->getWidgets($this->document) : $panel->getWidgets();

		foreach($widgets as $widget) { $widget->render($this); }
	?>
</div>
<?php
	include APPLICATION_HOME.'/includes/footer.inc';
	include FRAMEWORK.'/xhtmlFooter.inc';
?>
