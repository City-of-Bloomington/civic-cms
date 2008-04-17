<?php
/**
 * @copyright Copyright (C) 2006-2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
?>
<div id="footer">
	<div>
		<ul>
			<?php
				if(!isset($_SESSION['USER']))
				{
					echo "
					<li class=\"first\"><a href=\"".BASE_URL."/login\">Sign In</a></li>
					";
				}
				else
				{
					echo "
					<li class=\"first\"><a href=\"".BASE_URL."/login/logout.php\">Sign Out</a></li>
					";
				}
			?>
			<li><a href="<?php echo BASE_URL; ?>/documents/az_index.php">A-Z Index</a></li>
			<li><a href="<?php echo BASE_URL; ?>/website-privacy-statement">Privacy</a></li>
			<li><a href="<?php echo BASE_URL; ?>/Website-Accessibility-Statement">Accessibility</a></li>
			<li><a href="<?php echo BASE_URL; ?>/languages">Languages</a></li>
			<li><a href="<?php echo BASE_URL; ?>/feeds">Feeds</a></li>
			<li><a href="<?php echo BASE_URL; ?>/jobs">Jobs</a></li>
			<li><a href="<?php echo BASE_URL; ?>/search/sitemap.php">Sitemap</a></li>
		</ul>
		<ul><li><a href="http://validator.w3.org/check?uri=referer">Valid XHTML 1.0 Strict</a></li>
			<?php
				$css = BASE_URL."/skins/$_SESSION[skin]/screen.css";
			?>
			<li><a href="http://jigsaw.w3.org/css-validator/validator?uri=<?php echo $css; ?>">Valid CSS 2.1</a></li>
			<li><a href="http://www.w3.org/WAI/WCAG1A-Conformance" title="Explanation of Level A Conformance">W3C-WAI WCAG</a></li>
		</ul>
	</div>
</div>