<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Tag $this->tag
 */
?>
<h2>Update Tag</h2>
<form method="post" action="<?php echo $_SERVER['PHP_SELF']; ?>">
<fieldset><legend>Tag Info</legend>
	<input name="tag_id" type="hidden" value="<?php echo $this->tag->getId(); ?>" />

	<table>
	<tr><td><label for="tag-name" class="required">Name</label></td>
		<td><input name="tag[name]" id="tag-name" value="<?php echo View::escape($this->tag->getName()); ?>" /></td></tr>
	<tr><td><label for="tag-tagGroup_id" class="required">Group</label></td>
		<td><select name="tag[tagGroup_id]" id="tag-tagGroup_id">
			<?php
				$list = new TagGroupList();
				$list->find();
				foreach($list as $group)
				{
					$name = View::escape($group->getName());
					$selected = $this->tag->getTagGroup_id()==$group->getId() ? 'selected="selected"' : '';
					echo "<option value=\"{$group->getId()}\" $selected>$name</option>";
				}
			?>
			</select>
		</td>
	</tr>
	<tr><td colspan="2">
			<div><label for="description">Description</label></div>
			<?php
				$content = $this->tag->getDescription();
				$content_field_name = 'description';
				include APPLICATION_HOME.'/includes/editors/'.EDITOR.'/editor_init.inc';
			?>
	</td></tr>
	</table>

	<button type="submit" class="submit">Submit</button>
	<button type="button" class="cancel" onclick="document.location.href='<?php echo BASE_URL; ?>/tags';">Cancel</button>
</fieldset>
</form>
