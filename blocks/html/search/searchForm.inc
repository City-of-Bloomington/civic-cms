<?php
/**
 * @copyright 2007-2013 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
$search = !empty($_GET['search']) ? View::escape($_GET['search']) : '';
?>
<form method="get" action="<?php echo BASE_URL; ?>/search">
<fieldset><legend>Search</legend>
	<input name="search" size="60" value="<?php echo $search ?>" />
	<button type="submit" class="search">Search</button>
</fieldset>
</form>
