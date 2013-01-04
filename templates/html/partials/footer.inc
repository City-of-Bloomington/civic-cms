<?php
/**
 * @copyright 2006-2013 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
?>
<div id="footer">
	<div>
		<ul>
			<?php
				if (!isset($_SESSION['USER'])) {
					echo "<li class=\"first\"><a href=\"".BASE_URL."/login\">Sign In</a></li>";
				}
				else {
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
	</div>
</div>
<?php
	if (isset($this->assets['scripts'])) {
		foreach ($this->assets['scripts'] as $url) {
			echo "<script type=\"text/javascript\" src=\"$url\"></script>\n";
		}
	}
	if (isset($this->assets['stylesheets'])) {
		foreach ($this->assets['stylesheets'] as $url) {
			echo "<link rel=\"stylesheet\" href=\"$url\" />\n";
		}
	}
?>