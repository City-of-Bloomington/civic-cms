<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Document $this->document
 */
?>
<h2>Upload an Attachment</h2>
<form id="documentForm" method="post" action="<?php echo $_SERVER['PHP_SELF']; ?>" enctype="multipart/form-data">
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
		<button type="button" class="upload" onclick="processTabbedForm('documentForm','attachments','next');">Upload</button>
	</fieldset>

	<fieldset><legend>Next</legend>
		<p>Move on to the next tab.  The document will not be saved to the database until you click the "Save" button.</p>
		<input type="hidden" name="tab" id="tab" value="facets" />
		<input type="hidden" name="action" id="action" value="next" />
		<button type="submit" class="next">Next</button>
		<button type="cancel" class="cancel" onclick="self.close();">Cancel</button>
		<button type="button" class="save" onclick="processTabbedForm('documentForm','attachments','save');">Save</button>
	</fieldset>
</form>
