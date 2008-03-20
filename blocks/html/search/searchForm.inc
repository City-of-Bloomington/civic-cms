<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param string $this->search
 */
?>
<form method="get" action="<?php echo BASE_URL; ?>/search">
<fieldset><legend>Search</legend>
	<input name="search" size="60" value="<?php echo $this->search; ?>" />
	<button type="submit" class="search">Search</button>
</fieldset>
</form>
