<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param string $this->title
 */
	$startTime = microtime(1);
?>
<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1//EN" "http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd">
<html xmlns="http://www.w3.org/1999/xhtml"
     xml:lang="en" >
<head profile="http://dublincore.org/documents/dcq-html/">
	<title><?php echo View::escape($this->title); ?></title>
	<meta http-equiv="Content-Type" content="application/xhtml+xml; charset=utf-8" />
	<meta http-equiv="Content-Script-Type" content="text/javascript" />
	<meta name="robots" content="index,follow" />
	<meta name="Publisher" content="City of Bloomington Indiana 401 N Morton St. Bloomington IN 47403" />
	<meta name="Publisher-Email" content="webmaster@bloomington.in.gov" />
	<link rel="SHORTCUT ICON" href="<?php echo BASE_URL; ?>/favicon.ico" />
	<style type="text/css" media="screen">
		@import url('<?php echo BASE_URL."/skins/$_SESSION[skin]/screen.css"; ?>');
	</style>
	<style type="text/css" media="print">
		@import url('<?php echo BASE_URL."/skins/$_SESSION[skin]/print.css"; ?>');
	</style>
	<!--[if IE 6]>
	<style type="text/css" media="screen">@import url('<?php echo BASE_URL."/skins/$_SESSION[skin]/IE6.css"; ?>');</style>
	<![endif]-->
	<script type="text/javascript" src="<?php echo BASE_URL; ?>/js/functions.js"></script>

	<style type="text/css" media="screen">
		@import url('<?php echo BASE_URL; ?>/js/lightbox/css/lightbox.css');
	</style>

	<!-- Load the YUI toolkit -->
	<style type="text/css" media="screen">@import url('http://yui.yahooapis.com/2.5.2/build/assets/skins/sam/skin.css');</style>
	<style type="text/css" media="screen">@import url('http://yui.yahooapis.com/2.5.2/build/calendar/assets/skins/sam/calendar.css');</style>

	<?php
		if (isset($this->document))
		{
			$title = htmlspecialchars($this->document->getTitle(),ENT_QUOTES);
			$description = htmlspecialchars($this->document->getDescription(),ENT_QUOTES);
			$date = $this->document->getPublishDate('Y-m-d');

			echo "
			<link rel=\"schema.DC\" href=\"http://purl.org/dc/elements/1.1/\" />
			<meta name=\"DC.title\" content=\"$title\" />
			<meta name=\"DC.description\" content=\"$description\" />
			<meta name=\"DC.date\" content=\"$date\" />
			<meta name=\"DC.publisher\" content=\"City of Bloomington Indiana 401 N Morton St. Bloomington IN 47403\" />
			<meta name=\"DC.format\" content=\"text/xhtml\" />
			<meta name=\"DC.coverage\" content=\"Bloomington City Government\" />
			";
		}
	?>
</head>
<body id="top">
