<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Document $this->document
 */
?>
<h2>Upload an Attachment</h2>
<form method="post" action="<?php echo $_SERVER['PHP_SELF']; ?>" enctype="multipart/form-data">
<fieldset><legend>Attachment Info</legend>
	<table>
	<tr><td><label for="attachment-title" class="required">Title</label></td>
		<td><input name="attachment[title]" id="attachment-title" /></td></tr>
	<tr><td><label for="attachment-description" class="required">Description</label></td>
		<td><input name="attachment[description]" id="attachment-description" /></td></tr>
	</table>
</fieldset>
<fieldset><legend>Upload</legend>
	<input name="document_id" type="hidden" value="<?php echo $this->document->getId(); ?>" />
	<input name="attachment" type="file" />
	<button type="submit" class="upload">Upload</button>
</fieldset>
</form>
