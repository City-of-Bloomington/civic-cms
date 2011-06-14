<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Document $this->document
 * @param URL $this->return_url
 * @param int $this->instance_id
 */
?>
<div class="interfaceBox">
	<h2>Add a Related Link</h2>
	<p>Links created here will show up in a widget on the side of the page.</p>

	<form id="documentForm" method="post" action="<?php echo $_SERVER['SCRIPT_NAME']; ?>" enctype="multipart/form-data">
	<fieldset><legend>Link</legend>
		<input type="hidden" name="tab" id="tab" value="info" />
		<input type="hidden" name="action" id="action" value="next" />
		<input type="hidden" name="return_url" value="<?php echo $this->return_url; ?>" />
		<input type="hidden" name="instance_id" value="<?php echo $this->instance_id; ?>" />
		<input type="hidden" name="continue" id="continue" value="true" />
<?php
	# Make sure the document has been saved before we attempt to do links
	if ($this->document->getId())
	{
?>
		<table>
		<tr><td><label for="documentLink-title" class="required">Title</label></td>
			<td><input name="documentLink[title]" id="documentLink-title" size="60" /></td></tr>
		<tr><td><label for="documentLink-href" class="required">URL</label></td>
			<td><input name="documentLink[href]" id="documentLink-href" size="60" /></td></tr>
		<tr><td colspan="2">
				<div><label for="documentLink-description" class="required">Description</label></div>
				<textarea name="documentLink[description]" id="documentLink-description" rows="3" cols="60"></textarea>
		</td></tr>
		</table>

		<button type="button" class="add" onclick="FRAMEWORK.processTabbedForm('documentForm','links','next');">Add</button>
<?php
	}
	else
	{
		echo "<p>You cannot assign related links until the document has been saved.</p>";
	}
?>
	</fieldset>

	</form>
</div>
<div class="interfaceBox">
	<h2>Related Links</h2>
	<?php
		$links = new DocumentLinkList(array('document_id'=>$this->document->getId()));
		if (count($links))
		{
			echo '<ul>';
			foreach($links as $link)
			{
				echo "
				<li><button type=\"button\" class=\"deleteSmall\" onclick=\"removeLink({$link->getId()});\">Delete</button>
					<a href=\"{$link->getHref()}\">{$link->getTitle()}</a>
				</li>
				";
			}
			echo '</ul>';
		}
	?>
	<script type="text/javascript">
		var removalRequest = FRAMEWORK.getXMLHttpRequestObject();
		function removeLink(link_id)
		{
			removalRequest.open("get","<?php echo BASE_URL; ?>/documents/removeLink.php?link_id="+link_id);
			removalRequest.onreadystatechange = handleRemovalResult;
			removalRequest.send(null);
		}

		function handleRemovalResult()
		{
			if (removalRequest.readyState == 4)
			{
				FRAMEWORK.processTabbedForm('documentForm','links','next');
			}
		}
	</script>
</div>
