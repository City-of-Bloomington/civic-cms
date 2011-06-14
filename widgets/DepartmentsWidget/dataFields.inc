<?php
/**
 * @copyright Copyright (C) 2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Widget $this->widget
 */
	$content = View::escape($this->widget->content);
?>
<fieldset><legend>Custom Content</legend>
	<textarea name="content" rows="15" cols="60"><?php echo $content; ?></textarea>
</fieldset>
