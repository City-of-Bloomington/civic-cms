<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
?>
<div id="banner">
	<div id="location_name"><a href="<?php echo BASE_URL; ?>/">City of Bloomington, Indiana</a></div>
	<div id="navigation">
		<?php
			if (isset($_SESSION['USER'])) { echo "<a href=\"".BASE_URL."/login/logout.php\">Logout</a>"; }
			else { echo "<a href=\"".BASE_URL."/login\">Login</a>"; }
		?>
		<a href="az_index.html">A-Z Index</a>
		<a href="contacts.html">City Contacts</a>
		<a href="job_postings">Job Postings</a>
		<form method="get" action="<?php echo BASE_URL; ?>/documents/search.php">
		<div>
		<label for="search">SEARCH</label>
			<input name="search" id="search" value="bloomington.in.gov" onclick="this.value='';" />
			<button type="submit" class="search">search</button>
		</div>
		</form>
		<form method="get" action="<?php $_SERVER['REQUEST_URI']; ?>">
		<div><label for="skin">Skin</label>
			<select name="skin" id="skin" onchange="this.form.submit();">
			<?php
				$list = new DirectoryIterator(APPLICATION_HOME.'/html/skins');
				foreach($list as $dir)
				{
					if ($dir!='.' && $dir!='..')
					{
						if (is_file(APPLICATION_HOME."/html/skins/$dir/skin.css"))
						{
							$skin = basename($dir);
							$selected = (isset($_SESSION['skin']) && $_SESSION['skin']===$skin) ? 'selected="selected"' : '';
							echo "<option $selected>$skin</option>";
						}
					}
				}
			?>
			</select>
		</div>
		</form>
	</div>
</div>
