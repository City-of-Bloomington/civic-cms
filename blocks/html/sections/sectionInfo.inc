<?php
/**
 * @copyright Copyright (C) 2007,2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Section $this->section
 */
?>
<h1><?php echo View::escape($this->section->getName()); ?></h1>
<h2><?php echo View::escape($this->section->getNickname()); ?></h2>

<h3>Departments</h3>
<ul>
<?php
	foreach($this->section->getDepartments() as $department)
	{
		$name = View::escape($department->getName());
		echo "<li>$name</li>";
	}
?>
</ul>

<h3>Parents
	<a class="addSmall" href="<?php echo BASE_URL; ?>/sections/addParent.php?section_id=<?php echo $this->section->getId(); ?>">Add</a>
</h3>
<ul>
<?php
	foreach($this->section->getParentNodes() as $node)
	{
		$parent = $node->getParent();
		$name = View::escape($parent->getName());
		echo "
		<li>$name
			<a class=\"deleteSmall\" href=\"".BASE_URL."/sections/removeParent.php?sectionNode_id={$node->getId()}\">Remove</a>
		</li>
		";
	}
?>
</ul>

<?php
	if ($this->section->hasChildren())
	{
		echo "
		<h3>Children</h3>
		<form method=\"post\" action=\"$_SERVER[PHP_SELF]\">
		<fieldset><legend>Ordering</legend>
			<p>You can adjust the order of the child sections here.</p>
			<ul class=\"compact\">
		";
			foreach($this->section->getChildNodes() as $node)
			{
				$child = $node->getSection();
				$name = View::escape($child->getName());
				echo "
				<li><input name=\"nodePlacement[{$node->getId()}]\" id=\"nodePlacement-{$node->getId()}\" size=\"2\" maxlength=\"2\" value=\"{$node->getPlacement()}\" />
					<label for=\"nodePlacement-{$node->getId()}\">$name</label>
				</li>
				";
			}
		echo "
			</ul>
			<button type=\"submit\" class=\"save\">Save</button>
			<a class=\"cancel\" href=\"".BASE_URL."/sections\">Cancel</a>
		</fieldset>
		</form>
		";
	}
?>