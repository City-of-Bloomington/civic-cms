<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
?>
<h1>Upload a new Image</h1>
<form method="post" action="<?php echo $_SERVER['PHP_SELF']; ?>" enctype="multipart/form-data">
<fieldset><legend>Image Info</legend>
	<table>
	<tr><td><label for="image-title" class="required">Title</label></td>
		<td><input name="image[title]" id="image-title" size="60" /></td></tr>
	<tr><td><label for="image-description" class="required">Description</label></td>
		<td><textarea name="image[description]" id="image-description" rows="4" cols="60" onkeyup="FRAMEWORK.limit(this,255);"></textarea></td></tr>
	</table>
</fieldset>
<fieldset><legend>Upload</legend>
	<input name="image" type="file" />
	<button type="submit" class="upload">Upload</button>
</fieldset>
</form>
