<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param array $this->ancestors
 */
	echo "<div><ul>";
	foreach($this->ancestors as $i=>$section)
	{
		echo "<li><a href=\"".BASE_URL."/sections/viewSection.php?section_id={$section->getId()}\">$section</a>\n";

		if (count($this->ancestors) - $i <= 1)
		{
			echo "<ul>";
			# Expand this section
			foreach($section->getChildren() as $child)
			{
				if ($child->getId() == $this->section->getId())
				{
					echo "<li class=\"current\"><a href=\"".BASE_URL."/sections/viewSection.php?section_id={$child->getId()}\">$child</a>\n";
					echo "<ul>";
					foreach($this->section->getChildren() as $child)
					{
						echo "<li><a href=\"".BASE_URL."/sections/viewSection.php?section_id={$child->getId()}\">$child</a></li>\n";
					}
					echo "</ul>";
				}
				else { echo "<li><a href=\"".BASE_URL."/sections/viewSection.php?section_id={$child->getId()}\">$child</a>\n"; }

				echo "</li>";
			}
			echo "</ul>";
		}
		echo "</li>";
	}

	echo "</ul></div>";
?>