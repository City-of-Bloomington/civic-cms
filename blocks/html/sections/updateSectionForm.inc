<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Section $this->section
 */
	function printSectionOptions($section,$depth,$sectionToEdit,$currentSection)
	{
		$depthIndicator = str_repeat("-",$depth);
		$checked = $sectionToEdit->hasParent($section) ? "checked=\"checked\"" : "";
		echo "<li><label>";

		# Sections should not be allowed to be parents of themselves
		if ($section->getId() != $currentSection->getId())
		{
			echo "<input name=\"section[parents][{$section->getId()}]\" type=\"checkbox\" value=\"{$section->getId()}\" $checked />";
		}
		echo "$section</label></li>";
		if ($section->hasChildren())
		{
			echo "<ul>";
			foreach($section->getChildren() as $child) { printSectionOptions($child,$depth+1,$sectionToEdit,$currentSection); }
			echo "</ul>";
		}
	}
?>
<h1>Edit <?php echo $this->section; ?></h1>
<form method="post" action="<?php echo $_SERVER['PHP_SELF']; ?>">
<fieldset><legend>Section Info</legend>
	<input name="id" type="hidden" value="<?php echo $this->section->getId(); ?>" />
	<table>
	<tr><td><label for="section-name" class="required">Name</label></td>
		<td><input name="section[name]" id="section-name" value="<?php echo View::escape($this->section->getName()); ?>" /></td></tr>
	<tr><td><label for="section-nickname">Nickname</label></td>
		<td><input name="section[nickname]" id="nickname" value="<?php echo View::escape($this->section->getNickname()); ?>" /></td></tr>
	</table>
</fieldset>

<fieldset><legend class="required">Departments</legend>
	<p>Choose the departments that will be allowed to post content to this section.</p>
	<p>You must choose at least one.</p>
	<table>
	<?php
		$departments = new DepartmentList();
		$departments->find();
		foreach($departments as $department)
		{
			$name = View::escape($department->getName());
			$checked = $this->section->hasDepartment($department) ? "checked=\"checked\"" : "";
			echo "
			<tr><td><input type=\"checkbox\" name=\"section[departments][{$department->getId()}]\" id=\"section-departments-{$department->getId()}\" value=\"{$department->getId()}\" $checked /></td>
				<td><label for=\"section-departments-{$department->getId()}\">$name</label></td></tr>
			";
		}
	?>
	</table>
</fieldset>

<fieldset><legend>Submit</legend>
	<button type="submit" class="submit">Submit</button>
	<button type="button" class="cancel" onclick="document.location.href='<?php echo BASE_URL; ?>/sections/sectionInfo.php?section_id=<?php echo $this->section->getId(); ?>';">Cancel</button>
</fieldset>
</form>
