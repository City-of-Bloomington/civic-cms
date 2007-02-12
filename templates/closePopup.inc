<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
	include(APPLICATION_HOME."/includes/xhtmlTransitionalHeader.inc");
?>
<head>
	<meta http-equiv="Content-Type" content="application/xhtml+xml; charset=utf-8" />
	<meta http-equiv="Content-Script-Type" content="text/javascript" />
	<link rel="SHORTCUT ICON" href="/favicon.ico" />
	<style type="text/css" media="screen">
		@import url("<?php echo BASE_URL; ?>/skins/default/skin.css");
	</style>
	<title>Content Manager - City of Bloomington, Indiana</title>
</head>
<body onload="opener.location.reload();self.close();">
<?php
	include(FRAMEWORK."/errorMessages.inc");
	$this->includeBlocks();

	include(FRAMEWORK."/xhtmlFooter.inc");
?>