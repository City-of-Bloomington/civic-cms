<?php
/**
 * @copyright Copyright (C) 2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Section $this->section
 * @param srting $this->return_url
 */
?>
<h1>Notify Subscribers</h1>
<form method="post" action="<?php echo $_SERVER['PHP_SELF']; ?>">
<fieldset><legend>Message</legend>
	<input name="section_id" type="hidden" value="<?php echo $this->section->getId(); ?>" />
	<input name="return_url" type="hidden" value="<?php echo $this->return_url; ?>" />

	<div>
		<textarea name="message" rows="3" cols="60"></textarea>
	</div>

	<div>
		<button type="submit" class="submit">Submit</button>
		<a class="cancel" href="<?php echo $this->return_url; ?>">Cancel</a>
	</div>
</fieldset>

<fieldset><legend>Documents</legend>
	<p>Choose which documents you would like to include in the body of the email.</p>
	<table>
	<tr><th></th>
		<th>Document</th>
		<th>Updated</th>
	</tr>
	<?php
		$documents = $this->section->getDocuments('modified desc');
		foreach($documents as $document)
		{
			$title = View::escape($document->getTitle());
			$modified = $document->getModified('m/d/Y');
			echo "
			<tr><td><input name=\"documents[{$document->getId()}]\" id=\"documents-{$document->getId()}\" type=\"checkbox\" /></td>
				<td><label for=\"documents-{$document->getId()}\">$title</label></td>
				<td>$modified</td>
			</tr>
			";
		}
	?>
	</table>
</fieldset>
</form>
