<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
?>
<div id="banner">
	<div id="application_name"></div>
	<div id="location_name"><a href="<?php echo BASE_URL; ?>/">City of Bloomington, Indiana</a></div>
	<div id="navigation">
		<?php
			if (isset($_SESSION['USER'])) { echo "<a href=\"".BASE_URL."/login/logout.php\">Logout</a>"; }
			else { echo "<a href=\"".BASE_URL."/login\">Login</a>"; }
		?>
		<a href="<?php echo BASE_URL; ?>/directory">City Contacts</a>
		<a href="job_postings">Job Postings</a>
		<form method="get" action="<?php $_SERVER['PHP_SELF']; ?>">
		<fieldset>
			<?php
				$url = new URL($_SERVER['REQUEST_URI']);
				foreach($url->parameters as $field=>$value)
				{
					if ($field!='skin')
					{
						echo "<input name=\"$field\" type=\"hidden\" value=\"$value\" />";
					}
				}
			?>
			<label for="skin">Skin</label>
			<select name="skin" id="skin" onchange="this.form.submit();">
			<?php
				$list = new DirectoryIterator(APPLICATION_HOME.'/html/skins');
				foreach($list as $dir)
				{
					if ($dir!='.' && $dir!='..')
					{
						if (is_file(APPLICATION_HOME."/html/skins/$dir/screen.css"))
						{
							$skin = basename($dir);
							$selected = (isset($_SESSION['skin']) && $_SESSION['skin']===$skin) ? 'selected="selected"' : '';
							echo "<option $selected>$skin</option>";
						}
					}
				}
			?>
			</select>
			<?php
				# Since we're submitting the CSS changing as a FORM via GET
				# we need to make sure to preserve any parameters in the current URL
				$url = new URL($_SERVER['REQUEST_URI']);
				foreach($url->parameters as $key=>$value)
				{
					echo "<input name=\"$key\" type=\"hidden\" value=\"$value\" />";
				}
			?>
		</fieldset>
		</form>
	</div>
</div>
