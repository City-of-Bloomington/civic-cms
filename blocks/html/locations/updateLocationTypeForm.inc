<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param LocationType $this->locationType
 */
?>
<h1>Update LocationType</h1>
<form method="post" action="<?php echo $_SERVER['PHP_SELF']; ?>">
<fieldset><legend>Location Type Info</legend>
	<input name="id" type="hidden" value="<?php echo $this->locationType->getId(); ?>" />

	<table>
	<tr><td><label for="locationType-type" class="required">Type</label></td>
		<td><input name="locationType[type]" id="locationType-type" size="60" value="<?php echo $this->locationType->getType(); ?>" /></td></tr>
	</table>

	<button type="submit" class="submit">Submit</button>
	<a class="cancel" href="<?php echo BASE_URL; ?>/locations">Cancel</a>
</fieldset>
</form>
