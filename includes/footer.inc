<?php
/**
 * @copyright Copyright (C) 2006-2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
?>
<div id="footer">
	<div>
		<ul>
			<li><a href="<?php echo BASE_URL; ?>/documents/az_index.php">A-Z Index</a></li>
			<li><a href="<?php echo BASE_URL; ?>/website-privacy-statement">Privacy</a></li>
			<li><a href="<?php echo BASE_URL; ?>/Website-Accessibility-Statement">Accessibility</a></li>
			<li><a href="<?php echo BASE_URL; ?>/languages">Languages</a></li>
			<li><a href="<?php echo BASE_URL; ?>/feeds">Feeds</a></li>
			<li><a href="<?php echo BASE_URL; ?>/jobs">Jobs</a></li>
			<li><a href="<?php echo BASE_URL; ?>/search/sitemap.php">Sitemap</a></li>
			<li><?php
					if(!isset($_SESSION['USER'])) { echo '<a href="'.BASE_URL.'/login">Sign In</a>'; }
					else { echo '<a href="'.BASE_URL.'/login/logout.php">Sign Out</a>'; }
				?>
			</li>
			<li><a href="<?php echo BASE_URL; ?>/contact">Contact Us</a></li>
		</ul>
		<p class="copyright">
			Copyright (C) 2006-2008 City of Bloomington, Indiana. All rights reserved.
		</p>
	</div>
</div>
