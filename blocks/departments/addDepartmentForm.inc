<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
?>
<h1>New Department</h1>
<form method="post" action="<?php echo $_SERVER['PHP_SELF']; ?>">
<fieldset><legend>Department Info</legend>
	<table>
	<tr><td><label for="department-name">Name</label></td>
		<td><input name="department[name]" id="department-name" /></td></tr>
	</table>

	<button type="submit" class="submit">Submit</button>
	<button type="button" class="cancel" onclick="document.location.href='<?php echo BASE_URL; ?>/departments';">Cancel</button>
</fieldset>
</form>