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
		$name = $section->getNickname() ? View::escape($section->getNickname()) : View::escape($section->getName());
		echo "<li><a href=\"".BASE_URL."/sections/viewSection.php?section_id={$section->getId()}\">$section</a>\n";

		if (count($this->ancestors) - $i <= 1)
		{
			echo "<ul>";
			# Expand this section
			foreach($section->getChildren() as $child)
			{
				if ($child->getId() == $this->section->getId())
				{
					$name = $child->getNickname() ? View::escape($child->getNickname()) : View::escape($child->getName());
					echo "<li class=\"current\"><a href=\"".BASE_URL."/sections/viewSection.php?section_id={$child->getId()}\">$name</a>\n";
					echo "<ul>";
					foreach($this->section->getChildren() as $child)
					{
						$name = $child->getNickname() ? View::escape($child->getNickname()) : View::escape($child->getName());
						echo "<li><a href=\"".BASE_URL."/sections/viewSection.php?section_id={$child->getId()}\">$name</a></li>\n";
					}
					echo "</ul>";
				}
				else
				{
					$name = $child->getNickname() ? View::escape($child->getNickname()) : View::escape($child->getName());
					echo "<li><a href=\"".BASE_URL."/sections/viewSection.php?section_id={$child->getId()}\">$name</a>\n";
				}

				echo "</li>";
			}
			echo "</ul>";
		}
		echo "</li>";
	}

	echo "</ul></div>";
?>