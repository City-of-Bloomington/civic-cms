<?php
/**
 * @copyright Copyright (C) 2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Widget $this->widget
 */
	$title = View::escape($this->widget->title);
	$content = View::escape($this->widget->content);
?>
<fieldset><legend>Custom Content</legend>
<table>
<tr><td><label for="title">Title</label></td>
	<td><input name="title" id="title" size="60" value="<?php echo $title; ?>" /></td>
</tr>
<tr><td colspan="2">
		<textarea name="content" rows="15" cols="60"><?php echo $content; ?></textarea>
</td></tr>
</table>
</fieldset>
