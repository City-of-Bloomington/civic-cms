<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
/*
	$this->documentType
*/
?>
<h2>Edit <?php echo $this->documentType; ?></h2>
<form method="post" action="<?php echo $_SERVER['PHP_SELF']; ?>">
<fieldset><legend>Document Type</legend>
	<input name="documentType_id" type="hidden" value="<?php echo $this->documentType->getId(); ?>" />

	<table>
	<tr><td><label for="documentType-type">Type</label></td>
		<td><input name="documentType[type]" id="documentType-type" value="<?php echo $this->documentType->getType(); ?>" /></td></tr>
	<tr><td colspan="2">
		<label for="documentType-template">Template</label>
		<textarea name="documentType[template]" id="documentType-template" rows="20" cols="60"><?php echo $this->documentType->getTemplate(); ?></textarea>
		</td>
	</tr>
	</table>

	<button type="submit" class="submit">Save</button>
	<button type="button" class="cancel" onclick="document.location.href='<?php echo BASE_URL; ?>/documentTypes';">Cancel</button>
</fieldset>
</form>