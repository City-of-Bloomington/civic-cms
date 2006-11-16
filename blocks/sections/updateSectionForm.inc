<?php
/*
	$this->section
*/
	function printSectionOptions($section,$depth,$sectionToEdit)
	{
		$depthIndicator = str_repeat("-",$depth);
		if ($sectionToEdit->hasParent($section))
			{ echo "<option value=\"{$section->getId()}\" selected=\"selected\">$depthIndicator {$section->getName()}</option>"; }
		else { echo "<option value=\"{$section->getId()}\">$depthIndicator {$section->getName()}</option>"; }
		if ($section->hasChildren())
		{
			foreach($section->getChildren() as $child) { printSectionOptions($child,$depth+1,$sectionToEdit); }
		}
	}
?>
<form method="post" action="<?php echo $_SERVER['PHP_SELF']; ?>">
<fieldset><legend>Section Info</legend>
	<input name="id" type="hidden" value="<?php echo $this->section->getId(); ?>" />
	<table>
	<tr><td><label for="section-name">Name</label></td>
		<td><input name="section[name]" id="section-name" value="<?php echo $this->section->getName(); ?>" /></td></tr>
	<tr><td><label for="section-parents">Parents</label></td>
		<td><select name="section[parents][]" size="10" multiple="multiple"><option></option>
			<?php
				$sections = new SectionList(array("parent_id"=>"null"));
				foreach($sections as $section)
				{
					printSectionOptions($section,0,$this->section);
				}
			?>
			</select>
		</td>
	</tr>
	<tr><td><label for="section-department_id">Department</label></td>
		<td><select name="section[department_id]" id="section-department_id">
			<?php
				$departments = new DepartmentList();
				$departments->find();
				foreach($departments as $department)
				{
					if ($this->section->getDepartment_id() == $department->getId())
						{ echo "<option value=\"{$department->getId()}\" selected=\"selected\">{$department->getName()}</option>"; }
					else { echo "<option value=\"{$department->getId()}\">{$department->getName()}</option>"; }
				}
			?>
			</select>
		</td>
	</tr>
	</table>

	<button type="submit" class="submit">Submit</button>
	<button type="button" class="done" onclick="document.location.href='<?php echo BASE_URL; ?>/sections';">Done</button>
</fieldset>
</form>