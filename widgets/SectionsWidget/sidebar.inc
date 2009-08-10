<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Section $this->section The section we're displaying children of
 * @param array $this->currentSection The user's current section
 *
 * If the user is in a section that has no children, we display
 * the children of the parent section.  We don't want to forget where
 * the user is, though.
 */
?>
<div class="navigation widget">
	<h1>
	<?php
		$name = $this->section->getNickname()
				? $this->section->getNickname()
				: $this->section->getName();
		echo View::escape($name);
	?>
	</h1>
	<ul>
	<?php
		foreach($this->section->getChildren() as $section)
		{
			$name = $section->getNickname() ? $section->getNickname() : $section->getName();
			$name = View::escape($name);

			if (isset($this->currentSection) && $section->getId()==$this->currentSection->getId())
			{
				$class = 'class="current"';
			}
			else { $class = ''; }

			echo "<li><a href=\"{$section->getURL()}\" $class>$name</a></li>";
		}
	?>
	</ul>
</div>
