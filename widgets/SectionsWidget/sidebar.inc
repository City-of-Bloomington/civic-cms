<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Section $this->section
 * @param array $this->currentAncestors
 */
?>
<div class="widget">
	<h1>
	<?php
		echo View::escape($this->section->getName());
	?>
	</h1>
	<ul>
	<?php
		$currentSection = end($this->currentAncestors);
		foreach($this->section->getChildren() as $section)
		{
			$name = View::escape($section->getName());
			$class = $section->getId()==$currentSection->getId() ? 'class="current"' : '';
			echo "<li><a href=\"{$section->getURL()}\" $class>$name</a></li>";
		}
	?>
	</ul>
</div>