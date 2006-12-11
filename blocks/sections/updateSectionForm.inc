<?php
/*
	$this->section
*/
	function printSectionOptions($section,$depth,$sectionToEdit)
	{
		$depthIndicator = str_repeat("-",$depth);
		$checked = $sectionToEdit->hasParent($section) ? "checked=\"checked\"" : "";
		echo "<li><label><input name=\"section[parents][{$section->getId()}]\" type=\"checkbox\" value=\"{$section->getId()}\" $checked />$section</label></li>";
		if ($section->hasChildren())
		{
			echo "<ul>";
			foreach($section->getChildren() as $child) { printSectionOptions($child,$depth+1,$sectionToEdit); }
			echo "</ul>";
		}
	}
?>
<form method="post" action="<?php echo $_SERVER['PHP_SELF']; ?>">
<fieldset><legend>Section Info</legend>
	<input name="id" type="hidden" value="<?php echo $this->section->getId(); ?>" />
	<table>
	<tr><td><label for="section-name">Name</label></td>
		<td><input name="section[name]" id="section-name" value="<?php echo $this->section->getName(); ?>" /></td></tr>
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
	<tr><td><label for="section-placement">Placement</label></td>
		<td><input name="section[placement]" id="section-placement" size="2" maxlength="2" value="<?php echo $this->section->getPlacement(); ?>" /></td></tr>
	</table>
</fieldset>

<fieldset><legend>Parents</legend>
	<ul style="list-style-type:none">
		<?php
			$sections = new SectionList(array("parent_id"=>"null"));
			foreach($sections as $section)
			{
				printSectionOptions($section,0,$this->section);
			}
		?>
	</ul>
</fieldset>

<fieldset><legend>Widgets</legend>
<?php
	foreach(Widget::findInstalled() as $widget)
	{
		if ($this->section->hasWidget($widget)) { $checked = "checked=\"checked\""; } else { $checked = ""; }
		echo "<label><input type=\"checkbox\" name=\"section[widgets][$widget]\" value=\"$widget\" $checked />$widget</label>";
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
		if ($this->section->hasFacet($facet)) { $checked = "checked=\"checked\""; } else { $checked = ""; }
		echo "<label><input type=\"checkbox\" name=\"section[facets][{$facet->getId()}]\" value=\"{$facet->getId()}\" $checked />{$facet->getName()}</label>";
	}
*/
?>
</fieldset>

<fieldset><legend>Submit</legend>
	<button type="submit" class="submit">Submit</button>
	<button type="button" class="cancel" onclick="document.location.href='<?php echo BASE_URL; ?>/sections';">Cancel</button>
</fieldset>
</form>