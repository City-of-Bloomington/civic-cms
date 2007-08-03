<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Document $this->document
 */
?>
<div class="interfaceBox">
	<div class="titleBar">Links</div>
	<?php
		$links = new DocumentLinkList(array('document_id'=>$this->document->getId()));
		if (count($links))
		{
			echo '<ul>';
			foreach($links as $link)
			{
				echo "<li><a href=\"{$link->getHref()}\">{$link->getTitle()}</a></li>";
			}
			echo '</ul>';

		}
	?>
	<h2>Add a Link</h2>

	<form id="documentForm" method="post" action="<?php echo $_SERVER['PHP_SELF']; ?>" enctype="multipart/form-data">
	<fieldset><legend>Link</legend>
		<input type="hidden" name="tab" id="tab" value="info" />
		<input type="hidden" name="action" id="action" value="next" />

		<table>
		<tr><td><label for="documentLink-title">Title</label></td>
			<td><input name="documentLink[title]" id="documentLink-title" size="30" /></td></tr>
		<tr><td><label for="documentLink-href">URL</label></td>
			<td><input name="documentLink[href]" id="documentLink-href" size="30" /></td></tr>
		<tr><td colspan="2">
				<div><label for="documentLink-description">Description</label></div>
				<textarea name="documentLink[description]" id="documentLink-description" rows="3" cols="60"></textarea>
		</td></tr>
		</table>

		<button type="button" class="add" onclick="FRAMEWORK.processTabbedForm('documentForm','links','next');">Add</button>
	</fieldset>

	</form>
</div>
