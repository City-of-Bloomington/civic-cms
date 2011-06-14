<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
?>
<h1>Add LocationType</h1>
<form method="post" action="<?php echo $_SERVER['SCRIPT_NAME']; ?>">
<fieldset><legend>LocationType Info</legend>

	<table>
	<tr><td><label for="locationType-type" class="required">Type</label></td>
		<td><input name="locationType[type]" id="locationType-type" size="60" /></td></tr>
	</table>

	<button type="submit" class="submit">Submit</button>
	<a class="cancel" href="<?php echo BASE_URL; ?>/locations">Cancel</a>
</fieldset>
</form>
