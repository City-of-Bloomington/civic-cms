<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
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
<h1>New Section</h1>
<form method="post" action="<?php echo $_SERVER['PHP_SELF']; ?>">
<fieldset><legend>Section Info</legend>
	<table>
	<tr><td><label for="section-name">Name</label></td>
		<td><input name="section[name]" id="section-name" /></td></tr>
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
			$checked = $_SESSION['USER']->getDepartment_id()===$department->getId() ? 'checked="checked"' : '';
			echo "
			<tr><td><input type=\"checkbox\" name=\"section[departments][{$department->getId()}]\" id=\"section-departments-{$department->getId()}\" value=\"{$department->getId()}\" $checked /></td>
				<td><label for=\"section-departments-{$department->getId()}\">{$department->getName()}</label></td></tr>
			";
		}
	?>
	</table>
</fieldset>

<fieldset><legend class="required">Parents</legend>
	<p>Choose where in the site this section will show up.</p>
	<p>You must assign to it at least one place in the site.</p>

	<ul class="compact">
		<?php
			$sections = new SectionList(array("parent_id"=>"null"));
			foreach($sections as $section)
			{
				printSectionOptions($section,0);
			}
		?>
	</ul>
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
	<button type="submit" class="save">Save</button>
	<button type="button" class="cancel" onclick="document.location.href='<?php echo BASE_URL; ?>/sections';">Cancel</button>
</fieldset>
</form>
