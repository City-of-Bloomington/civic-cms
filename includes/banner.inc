<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
?>
<div class="menuBar">
<ul>
	<li><a href="<?php echo BASE_URL; ?>/documentTypes/documents.php?documentType_id=4">Services</a></li>
	<li><a href="<?php echo BASE_URL; ?>/documentTypes/documents.php?documentType_id=5">News</a></li>
	<li><a href="<?php echo BASE_URL; ?>/calendars">Events</a></li>
	<li><a href="<?php echo BASE_URL; ?>/locations">Locations</a></li>
	<li><a href="<?php echo BASE_URL; ?>/community_profile">Profile</a></li>
	<li><a href="<?php echo BASE_URL; ?>/documents/az_index.php">A-Z Index</a></li>
	<li><a href="<?php echo BASE_URL; ?>/jobs">Jobs</a></li>
	<li><a href="<?php echo BASE_URL; ?>/directory">Contacts</a></li>
</ul>
</div>
<div id="banner">
	<div id="application_name"></div>
	<div id="location_name"><a href="<?php echo BASE_URL; ?>/">City of Bloomington, Indiana</a></div>
	<div id="navigation">
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
		Take Action
		<?php
			$actions = new FacetGroup('Act Up');
			foreach($actions->getFacets() as $facet)
			{
				$name = View::escape($facet->getName());
				echo "<a href=\"{$facet->getURL()}\">$name</a> ";
			}
		?>
	</div>
</div>
