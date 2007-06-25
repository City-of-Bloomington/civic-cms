<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Department $this->department
 */
?>
<h1>Edit <?php echo $this->department; ?></h1>
<form method="post" action="<?php echo $_SERVER['PHP_SELF']; ?>">
<fieldset><legend>Department Info</legend>
	<input name="department_id" type="hidden" value="<?php echo $this->department->getId(); ?>" />
	<table>
	<tr><td><label for="department-name">Name</label></td>
		<td><input name="department[name]" id="department-name" value="<?php echo View::escape($this->department->getName()); ?>" /></td></tr>
	</table>

	<button type="submit" class="submit">Submit</button>
	<button type="button" class="cancel" onclick="document.location.href='<?php echo BASE_URL; ?>/departments';">Cancel</button>
</fieldset>
</form>
