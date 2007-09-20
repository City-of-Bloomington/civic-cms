<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Section $this->section
 */
	if (count($this->section->getChildren()))
	{
		$name = View::escape($this->section->getName());
		echo "
		<div class=\"interfaceBox subsections\">
			<h3>Sections in $name</h3>
			<ul>
		";
		foreach($this->section->getChildren() as $child)
		{
			$name = View::escape($child->getName());
			echo "<li><a href=\"".BASE_URL."/sections/viewSection.php?section_id={$child->getId()}\">$name</a></li>";
		}
		echo "
			</ul>
		</div>
		";
	}
