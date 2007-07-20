<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
	function printSectionOptions($section,$depth)
	{
		$name = View::escape($section->getName());
		$depthIndicator = str_repeat("-",$depth);
		echo "<li><label><input name=\"section[parents][{$section->getId()}]\" type=\"checkbox\" value=\"{$section->getId()}\" />$name</label></li>";
		if ($section->hasChildren())
		{
			echo "<ul style=\"list-style-type:none\">";
			foreach($section->getChildren() as $child) { printSectionOptions($child,$depth+1); }
			echo "</ul>";
		}
	}
?>
<h1>New Section</h1>
<form method="post" action="<?php echo $_SERVER['PHP_SELF']; ?>">
<fieldset><legend>Section Info</legend>
	<table>
	<tr><td><label for="section-name" class="required">Name</label></td>
		<td><input name="section[name]" id="section-name" /></td></tr>
	<tr><td><label for="section-nickname">Nickname</label></td>
		<td><input name="section[nickname]" id="nickname" /></td></tr>
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
			$checked = $_SESSION['USER']->getDepartment_id()===$department->getId() ? 'checked="checked"' : '';
			echo "
			<tr><td><input type=\"checkbox\" name=\"section[departments][{$department->getId()}]\" id=\"section-departments-{$department->getId()}\" value=\"{$department->getId()}\" $checked /></td>
				<td><label for=\"section-departments-{$department->getId()}\">$name</label></td></tr>
			";
		}
	?>
	</table>
</fieldset>

<fieldset><legend>Submit</legend>
	<button type="submit" class="save">Save</button>
	<button type="button" class="cancel" onclick="document.location.href='<?php echo BASE_URL; ?>/sections';">Cancel</button>
</fieldset>
</form>
