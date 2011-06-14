<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param string $this->search
 */
?>
<form method="get" action="<?php echo BASE_URL; ?>/search">
<fieldset><legend>Search</legend>
	<input name="search" size="60" value="<?php echo View::escape($this->search); ?>" />
	<button type="submit" class="search">Search</button>
</fieldset>
</form>
