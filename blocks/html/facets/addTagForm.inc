<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
?>
<h2>Add Tag</h2>
<form method="post" action="<?php echo $_SERVER['PHP_SELF']; ?>">
<fieldset><legend>Tag Info</legend>

	<table>
	<tr><td><label for="tag-name" class="required">Name</label></td>
		<td><input name="tag[name]" id="tag-name" /></td></tr>
	<tr><td><label for="tag-tagGroup_id" class="required">Group</label></td>
		<td><select name="tag[tagGroup_id]" id="tag-tagGroup_id">
			<?php
				$list = new TagGroupList();
				$list->find();
				foreach($list as $group)
				{
					$name = View::escape($group->getName());
					echo "<option value=\"{$group->getId()}\">$name</option>";
				}
			?>
			</select>
		</td>
	</tr>
	<tr><td colspan="2">
			<div><label for="description">Description</label></div>
			<?php
				$content = '';
				$content_field_name = 'description';
				include APPLICATION_HOME.'/includes/editors/'.EDITOR.'/editor_init.inc';
			?>
	</td></tr>
	</table>

	<button type="submit" class="submit">Submit</button>
	<button type="button" class="cancel" onclick="document.location.href='<?php echo BASE_URL; ?>/tags';">Cancel</button>
</fieldset>
</form>
