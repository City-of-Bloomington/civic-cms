<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
?>
<h2>New Document Type</h2>
<form method="post" action="<?php echo $_SERVER['PHP_SELF']; ?>">
<fieldset><legend>Document Type</legend>
	<table>
	<tr><td><label for="documentType-type">Type</label></td>
		<td><input name="documentType[type]" id="documentType-type" /></td></tr>
	<tr><td><label for="documentType-ordering">Ordering</label></td>
		<td><input name="documentType[ordering]" id="documentType-ordering" value="title" /></td></tr>
	<tr><td colspan="2">
		<label for="documentType-template">Template</label>
		<textarea name="documentType[template]" id="documentType-template" rows="20" cols="60"></textarea>
		</td>
	</tr>
	</table>

	<button type="submit" class="submit">Submit</button>
	<button type="button" class="cancel" onclick="document.location.href='<?php echo BASE_URL; ?>/documentTypes';">Cancel</button>
</fieldset>
</form>
