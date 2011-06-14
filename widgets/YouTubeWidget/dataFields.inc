<?php
/**
 * @copyright Copyright (C) 2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
print_r($this->widget);
?>
<fieldset><legend>YouTube Feed</legend>
	<p>Enter the URL of the YouTube feed.</p>
	<table>
	<tr><td><label for="XMLFeedURL">Feed URL</label></td>
		<td><input name="XMLFeedURL" id="XMLFeedURL" value="<?php echo View::escape($this->widget->XMLFeedURL); ?>" size="50" /></td>
	</tr>

	<tr><td><label for="numVideosToDisplay">Number of Videos</td>
		<td><input name="numVideosToDisplay" id="numVideosToDisplay" value="<?php echo View::escape($this->widget->numVideosToDisplay); ?>" size="3" /></td>
	</tr>
	</table>
</fieldset>
