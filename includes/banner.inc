<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
?>
<div id="banner">
	<div id="top" class="menuBar">
	<ul>
		<li><a href="<?php echo BASE_URL; ?>/documentTypes/documents.php?documentType_id=4">Services</a></li>
		<li><a href="<?php echo BASE_URL; ?>/documentTypes/documents.php?documentType_id=5">News</a></li>
		<li><a href="<?php echo BASE_URL; ?>/calendars">Events</a></li>
		<li><a href="<?php echo BASE_URL; ?>/locations">Locations</a></li>
		<li><a href="<?php echo BASE_URL; ?>/community_profile">Profile</a></li>
		<li><a href="<?php echo BASE_URL; ?>/search/sitemap.php">Sitemap</a></li>
	</ul>
	<ul>
		<?php
			if(!isset($_SESSION['USER']))
			{
				echo "
				<li><a href=\"".BASE_URL."/login\">Sign In</a></li>
				<li><a href=\"".BASE_URL."/login\">Subscribe</a></li>
				";
			}
			else
			{
				echo "
				<li><a href=\"".BASE_URL."/login/logout.php\">Sign Out</a></li>
				<li><a href=\"".BASE_URL."/sections/subscriptions\">Subscribe</a></li>
				";
			}
		?>
		<li><?php include APPLICATION_HOME.'/blocks/html/search/searchForm.inc'; ?></li>
	</ul>
	</div>
	<div id="application_name">
	</div>
	<div id="location_name"><a href="<?php echo BASE_URL; ?>/">City of Bloomington, Indiana</a></div>
	<div class="widgets">
		<?php
			$panel = new Panel('banner');
			$widgets = isset($this->document) ? $panel->getWidgets($this->document) : $panel->getWidgets();

			foreach($widgets as $widget) { $widget->render($this); }
		?>
	</div>
</div>
