<?php
/**
 * @copyright 2006-2009 City of Bloomington, Indiana
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param string $this->title
 */
$startTime = microtime(1);

$skin = isset($_GET['skin']) ? $_GET['skin'] : DEFAULT_SKIN;
$dublinCoreMetaTags = '';
if (isset($this->document)) {
	if ($this->document->getSkin()) {
		$skin = $this->document->getSkin();
	}

	$title = htmlspecialchars($this->document->getTitle(),ENT_QUOTES);
	$description = htmlspecialchars($this->document->getDescription(),ENT_QUOTES);
	$date = $this->document->getPublishDate('Y-m-d');

	$dublinCoreMetaTags = "
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
	<meta name="verify-v1" content="qf+tXEzM1CfhMG2IHbHh7jb4oRYLgqJ1oed1QZXnqvs=" />
	<link rel="SHORTCUT ICON" href="<?php echo BASE_URL; ?>/favicon.ico" />
	<style type="text/css" media="screen">
		@import url('<?php echo BASE_URL."/skins/$skin/screen.css"; ?>');
	</style>
	<style type="text/css" media="print">
		@import url('<?php echo BASE_URL."/skins/$skin/print.css"; ?>');
	</style>
	<!--[if IE 6]>
	<style type="text/css" media="screen">@import url('<?php echo BASE_URL."/skins/$skin/IE6.css"; ?>');</style>
	<![endif]-->
	<script type="text/javascript" src="<?php echo BASE_URL; ?>/js/functions.js"></script>

	<!-- Load the YUI Toolkit -->
	<style type="text/css" media="screen">
		@import url('<?php echo BASE_URL; ?>/js/yui/build/assets/skins/sam/skin.css');
		@import url('<?php echo BASE_URL; ?>/js/yui/build/calendar/assets/skins/sam/calendar.css');
	</style>
	<script src="<?php echo BASE_URL; ?>/js/yui/build/utilities/utilities.js" type="text/javascript"></script>
	<script src="<?php echo BASE_URL; ?>/js/yui/build/yahoo-dom-event/yahoo-dom-event.js" type="text/javascript"></script>
	<script src="<?php echo BASE_URL; ?>/js/yui/build/element/element-min.js" type="text/javascript"></script>
	<script src="<?php echo BASE_URL; ?>/js/yui/build/carousel/carousel-min.js" type="text/javascript"></script>
	<script src="<?php echo BASE_URL; ?>/js/yui/build/animation/animation-min.js" type="text/javascript"></script>
	<script src="<?php echo BASE_URL; ?>/js/yui/build/connection/connection-min.js" type="text/javascript"></script>
	<script src="<?php echo BASE_URL; ?>/js/yui/build/yahoo/yahoo-min.js" type="text/javascript"></script>
	<script src="<?php echo BASE_URL; ?>/js/yui/build/event/event-min.js" type="text/javascript"></script>

	<?php
		if (isset($this->document) && $this->document->getId()==1) {
			echo "
			<style type=\"text/css\" media=\"screen\">
				@import url('".BASE_URL."/skins/slideshow/slideshow.css');
			</style>
			";
		}
		echo $dublinCoreMetaTags;
	?>
</head>
<body id="top">
