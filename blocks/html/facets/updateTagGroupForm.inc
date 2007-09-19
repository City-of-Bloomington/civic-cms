<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param TagGroup $this->tagGroup
 */
?>
<h1>Update Tag Group</h1>
<form method="post" action="<?php echo $_SERVER['PHP_SELF']; ?>">
<fieldset><legend>Tag Group Info</legend>
	<input name="tagGroup_id" type="hidden" value="<?php echo $this->tagGroup->getId(); ?>" />

	<table>
	<tr><td><label for="tagGroup-name" class="required">Name</label></td>
		<td><input name="tagGroup[name]" id="tagGroup-name" value="<?php echo $this->tagGroup->getName(); ?>" /></td></tr>
	</table>
</fieldset>

<fieldset><legend>Related Groups</legend>
<p>When showing this tag, the system will also display any related documents of tags from the the groups you select here.</p>
<?php
	$list = new TagGroupList();
	$list->find();
	foreach($list as $group)
	{
		$name = View::escape($group->getName());
		$checked = in_array($group->getId(),array_keys($this->tagGroup->getRelatedGroups())) ? 'checked="checked"' : '';
		echo "
		<label>
			<input name=\"tagGroup[relatedGroups][{$group->getId()}]\" id=\"tagGroup-relatedGroups-{$group->getId()}\" value=\"{$group->getId()}\" type=\"checkbox\" $checked />
			$name
		</label>
		";
	}
?>
</fieldset>

<fieldset><legend>Departments</legend>
	<p>Choose the departments that are allowed to assign the Tags from inside this group to Documents.</p>
	<table>
	<?php
		$list = new DepartmentList();
		$list->find();
		foreach($list as $department)
		{
			$name = View::escape($department->getName());
			$checked = $this->tagGroup->hasDepartment($department) ? 'checked="checked"' : '';
			echo "
			<tr><td><input type=\"checkbox\" name=\"tagGroup[departments][{$department->getId()}]\" id=\"tagGroup-departments-{$department->getId()}\" value=\"{$department->getId()}\" $checked /></td>
				<td><label for=\"tagGroup-departments-{$department->getId()}\">$name</label></td></tr>
			";
		}
	?>
	</table>
</fieldset>

<fieldset><legend>Submit</legend>
	<button type="submit" class="submit">Submit</button>
	<button type="button" class="cancel" onclick="document.location.href='<?php echo BASE_URL; ?>/tags';">Cancel</button>
</fieldset>
</form>
