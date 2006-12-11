<?php
	function printSectionOptions($section,$depth)
	{
		$depthIndicator = str_repeat("-",$depth);
		echo "<li><label><input name=\"section[parents][{$section->getId()}]\" type=\"checkbox\" value=\"{$section->getId()}\" />$section</label></li>";
		if ($section->hasChildren())
		{
			echo "<ul style=\"list-style-type:none\">";
			foreach($section->getChildren() as $child) { printSectionOptions($child,$depth+1); }
			echo "</ul>";
		}
	}
?>
<form method="post" action="<?php echo $_SERVER['PHP_SELF']; ?>">
<fieldset><legend>Section Info</legend>
	<table>
	<tr><td><label for="section-name">Name</label></td>
		<td><input name="section[name]" id="section-name" /></td></tr>
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
	<tr><td><label for="section-placement">Placement</label></td>
		<td><input name="section[placement]" id="section-placement" size="2" maxlength="2" /></td></tr>
	</table>
</fieldset>

<fieldset><legend>Parents</legend>
	<ul style="list-style-type:none">
		<?php
			$sections = new SectionList(array("parent_id"=>"null"));
			foreach($sections as $section)
			{
				printSectionOptions($section,0);
			}
		?>
	</ul>
</fieldset>

<fieldset><legend>Widgets</legend>
<?php
	foreach(Widget::findInstalled() as $widget)
	{
		echo "<label><input type=\"checkbox\" name=\"section[widgets][$widget]\" value=\"$widget\" />$widget</label>";
	}
?>
</fieldset>

<fieldset><legend>Facets</legend>
<?php
/*
	$facets = new FacetList();
	$facets->find();
	foreach($facets as $facet)
	{
		echo "<label><input type=\"checkbox\" name=\"section[facets][{$facet->getId()}]\" value=\"{$facet->getId()}\" />{$facet->getName()}</label>";
	}
*/
?>
</fieldset>

<fieldset><legend>Submit</legend>
	<button type="submit" class="submit">Submit</button>
	<button type="button" class="done" onclick="document.location.href='<?php echo BASE_URL; ?>/sections';">Done</button>
</fieldset>
</form>