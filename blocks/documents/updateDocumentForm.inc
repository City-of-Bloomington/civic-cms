<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
/*
	$this->document
	$this->FCKeditor
*/
?>
<form method="post" action="<?php echo $_SERVER['PHP_SELF']; ?>">
	<fieldset><legend>Document Info</legend>
		<input name="document_id" type="hidden" value="<?php echo $this->document->getId(); ?>" />
		<table>
		<tr><td><label for="document-title">Title</label></td>
			<td><input name="document[title]" id="document-title" value="<?php echo $this->document->getTitle(); ?>" /></td></tr>
		</table>
		<?php $this->FCKeditor->create(); ?>
	</fieldset>

	<fieldset><legend>Sections</legend>
	</fieldset>

	<fieldset><legend>Facets</legend>
	</fieldset>

	<fieldset><legend>Submit</legend>
		<button type="submit" class="submit">Submit</button>
		<button type="button" class="cancel" onclick="document.location.href='<?php echo BASE_URL; ?>/documents/viewDocument.php?document_id=<?php echo $this->document->getId(); ?>';">Cancel</button>
	</fieldset>
</form>