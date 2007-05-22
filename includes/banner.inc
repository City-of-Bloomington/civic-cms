<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
?>
<div id="banner">
	<div id="application_name"><a href="<?php echo BASE_URL; ?>">Content Manager</a></div>
	<div id="location_name"><a href="<?php echo BASE_URL; ?>">City of Bloomington, Indiana</a></div>
	<div id="navigation">
		<?php
			if (isset($_SESSION['USER'])) { echo "<a href=\"".BASE_URL."/login/logout.php\">Logout</a>"; }
			else { echo "<a href=\"".BASE_URL."/login\">Login</a>"; }
		?>
	</div>
</div>
