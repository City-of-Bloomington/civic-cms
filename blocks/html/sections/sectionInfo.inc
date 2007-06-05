<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Section $this->section
 */
?>
<h2><?php echo $this->section; ?></h2>

<h3>Departments</h3>
<ul>
<?php
	foreach($this->section->getDepartments() as $department)
	{
		echo "<li>$department</li>";
	}
?>
</ul>

<h3>Parents
	<button type="button" class="addSmall" onclick="document.location.href='<?php echo BASE_URL; ?>/sections/addParent.php?section_id=<?php echo $this->section->getId(); ?>';">Add</button>
</h3>
<ul>
<?php
	foreach($this->section->getParentNodes() as $node)
	{
		$parent = $node->getParent();
		echo "
		<li>$parent
			<button type=\"button\" class=\"deleteSmall\" onclick=\"document.location.href='".BASE_URL."/sections/removeParent.php?sectionNode_id={$node->getId()}';\">Remove</button>
		</li>
		";
	}
?>
</ul>
