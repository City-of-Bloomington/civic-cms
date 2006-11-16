<?php
	function printSectionOptions($section,$depth)
	{
		$depthIndicator = str_repeat("-",$depth);
		echo "<option value=\"{$section->getId()}\">$depthIndicator".View::sanitizeString($section->getName())."</option>";
		if ($section->hasChildren())
		{
			foreach($section->getChildren() as $child) { printSectionOptions($child,$depth+1); }
		}
	}
?>
<form method="post" action="<?php echo $_SERVER['PHP_SELF']; ?>">
<fieldset><legend>Section Info</legend>
	<table>
	<tr><td><label for="section-name">Name</label></td>
		<td><input name="section[name]" id="section-name" /></td></tr>
	<tr><td><label for="section-parents">Parents</label></td>
		<td><select name="section[parents][]" size="10" multiple="multiple"><option></option>
			<?php
				$sections = new SectionList(array("parent_id"=>1));
				foreach($sections as $section)
				{
					printSectionOptions($section,0);
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
				foreach($departments as $department) { echo "<option value=\"{$department->getId()}\">{$department->getName()}</option>"; }
			?>
			</select>
		</td>
	</tr>
	</table>

	<button type="submit" class="submit">Submit</button>
	<button type="button" class="done" onclick="document.location.href='<?php echo BASE_URL; ?>/sections';">Done</button>
</fieldset>
</form>