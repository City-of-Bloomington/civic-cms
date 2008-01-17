<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
?>
<div id="footer">
	<div class="menuBar">
	<ul><li><a href="<?php echo BASE_URL; ?>">Home</a></li>
		<li><a href="<?php echo BASE_URL; ?>/Website-Accessibility-Statement">Accessibility</a></li>
		<li><a href="<?php echo BASE_URL; ?>/website-privacy-statement">Privacy</a></li>
		<li><a href="<?php echo BASE_URL; ?>/contact">Contact the City</li>
		<li><a href="<?php echo BASE_URL; ?>/city-website">About this Website</a></li>
	</ul>
	</div>
	<div class="menuBar">
	<ul><li>
		<?php
			if(!isset($_SESSION['USER'])) { echo '<a href="'.BASE_URL.'/login">Login</a>'; }
			else { echo '<a href="'.BASE_URL.'/login/logout.php">Logout</a>'; }
		?>
		</li>
		<li><a href="http://locutus.bloomington.in.gov:8080/secure/CreateIssue!default.jspa?pid=10031&amp;issuetype=1">Report a problem</a></li>
		<li><a href="<?php echo BASE_URL; ?>/skins">Choose a Skin</a></li>
	</ul>
	</div>
	<div><a href="http://validator.w3.org/check?uri=referer">
			<img src="<?php echo BASE_URL; ?>/media/media.php?media_id=1601" alt="Valid XHTML 1.0 Strict" height="31" width="88" /></a>
		<a href="http://jigsaw.w3.org/css-validator">
			<img src="<?php echo BASE_URL; ?>/media/media.php?media_id=1605" alt="Valid CSS" height="31" width="88" /></a>
		<a href="http://www.w3.org/WAI/WCAG1A-Conformance" title="Explanation of Level A Conformance">
			<img src="<?php echo BASE_URL; ?>/media/media.php?media_id=1736" alt="Level A conformance icon, W3C-WAI Web Content Accessibility Guidelines 1.0" height="32" width="88" /></a>
	</div>
	<?php include FRAMEWORK.'/footer.inc'; ?>
</div>
