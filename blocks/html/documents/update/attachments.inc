<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Document $this->document
 * @param URL $this->return_url
 * @param int $this->instance_id
 */
?>
<h1>Add an Attachment</h1>
<form id="documentForm" method="post" action="<?php echo $_SERVER['PHP_SELF']; ?>" enctype="multipart/form-data">
	<fieldset><legend>Browse</legend>
		<input type="hidden" name="tab" id="tab" value="links" />
		<input type="hidden" name="action" id="action" value="next" />
		<input type="hidden" name="return_url" value="<?php echo $this->return_url; ?>" />
		<input type="hidden" name="instance_id" value="<?php echo $this->instance_id; ?>" />
		<input type="hidden" name="continue" id="continue" value="true" />


		<p>Browse for an existing file.</p>
		<button type="button" class="browse" onclick="window.open('<?php echo BASE_URL; ?>/documents/mediaSelector.php');">Browse</button>
		<input type="hidden" name="attachment[media_id]" id="attachment-media_id" />
	</fieldset>
	<fieldset><legend>Upload a new file</legend>
		<table>
		<tr><td><label for="attachment-title" class="required">Title</label></td>
			<td><input name="attachment[title]" id="attachment-title" /></td></tr>
		<tr><td><label for="attachment-description" class="required">Description</label></td>
			<td><textarea name="attachment[description]" id="attachment-description" rows="3" cols="60"></textarea></td></tr>
		</table>
		<input name="max_file_size" type="hidden" value="<?php echo 1000000 * (int)ini_get('upload_max_filesize'); ?>" />
		<input name="attachment" type="file" />
		<button type="button" class="upload" onclick="FRAMEWORK.processTabbedForm('documentForm','attachments','next');">Upload</button>
	</fieldset>

</form>

<div class="interfaceBox">
	<div class="titleBar">Attachments</div>
	<table>
	<?php
		$list = new MediaList(array('document_id'=>$this->document->getId()));
		foreach($list as $attachment)
		{
			$title = View::escape($attachment->getTitle());
			echo "
			<tr><td><a class=\"{$attachment->getExtension()}\">{$attachment->getFilename()}</a></td>
				<td>$title</td>
				<td><button type=\"button\" class=\"deleteSmall\" onclick=\"removeAttachment({$attachment->getId()});\">Delete</button></td>
			</tr>
			";
		}
	?>
	</table>
	<script type="text/javascript">
		var removalRequest = FRAMEWORK.getXMLHttpRequestObject();
		function removeAttachment(media_id)
		{
			removalRequest.open("get","<?php echo BASE_URL; ?>/documents/removeAttachment.php?document_id=<?php echo $this->document->getId(); ?>;media_id="+media_id);
			removalRequest.onreadystatechange = handleRemovalResult;
			removalRequest.send(null);
		}

		function handleRemovalResult()
		{
			if (removalRequest.readyState == 4)
			{
				FRAMEWORK.processTabbedForm('documentForm','attachments','next');
			}
		}

		function addAttachment(media_id)
		{
			document.getElementById('attachment-media_id').value = media_id;
			FRAMEWORK.processTabbedForm('documentForm','attachments','next');
		}
	</script>
</div>
