<?php
/**
 * @copyright 2006-2009 City of Bloomington, Indiana.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param string $this->title
 */
if (!isset($this->title)) { $this->title = "City of Bloomington"; }
$startTime = microtime(1);

$skin = isset($_GET['skin']) ? $_GET['skin'] : DEFAULT_SKIN;
$skin = isset($this->document)&&$this->document->getSkin() ? $this->document->getSkin() : $skin;
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
		@import url('<?php echo BASE_URL."/skins/$skin/print.css"; ?>');
	</style>
	<script type="text/javascript" src="<?php echo BASE_URL; ?>/js/functions.js"></script>
	<title><?php echo View::escape($this->title); ?></title>
</head>
<body>
<?php
	include APPLICATION_HOME.'/templates/html/partials/banner.inc';
	include APPLICATION_HOME.'/templates/html/partials/menubar.inc';
?>
<div id="main-content-container">
<?php
	include APPLICATION_HOME.'/templates/html/partials/leftSidebar.inc';
	if (isset($this->document)) { include APPLICATION_HOME.'/templates/html/partials/pageTools.inc'; }
	include APPLICATION_HOME.'/templates/html/partials/rightSidebar.inc';
?>
<div id="mainContent" xml:lang="<?php echo $_SESSION['LANGUAGE']; ?>">
	<?php
		include FRAMEWORK.'/errorMessages.php';

		echo $this->includeBlocks();

		$panel = new Panel('mainContent');
		$widgets = isset($this->document) ? $panel->getWidgets($this->document) : $panel->getWidgets();

		foreach($widgets as $widget) { $widget->render($this); }
	?>
</div>
</div>
<?php
	include APPLICATION_HOME.'/templates/html/partials/footer.inc';
?>
</body>
</html>
