<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param array $this->ancestors
 * @param Section $this->section
 * @param Document $this->document
 */
	# Figure out what point in the ancestral line we want
	# to start expanding the list
	$numAncestors = count($this->ancestors);
	$targetCount = ($numAncestors-2 < 1) ? 1 : $numAncestors-2;

	echo "<div><ul>";
	$count = 0;
	foreach($this->ancestors as $i=>$section)
	{
		$count++;
		$name = View::escape($section->getName());

		# We want to display all the Uncles and Aunts for the current section
		# We can get these by grabbing all children from the third to last ancestor
		# The third to last should be the grandparent of the current section
		if ($count == $targetCount)
		{
			echo "<li><a href=\"".BASE_URL."/sections/viewSection.php?section_id={$section->getId()}\">$name</a><ul>";
			foreach($section->getChildren() as $uncle)
			{
				$name = View::escape($uncle);
				echo "<li><a href=\"".BASE_URL."/sections/viewSection.php?section_id={$uncle->getId()}\">$name</a>";

				# If we hit the parent of the current section, list all of its' children
				# These are the siblings of the current section
				if (($uncle->getId()==$this->section->getId()) ||
					(in_array($uncle->getId(),array_keys($this->ancestors))))
				{
					echo "<ul>";
					foreach($uncle->getChildren() as $sibling)
					{
						$name = View::escape($sibling->getName());
						echo "<li><a href=\"".BASE_URL."/sections/viewSection.php?section_id={$sibling->getId()}\">$name</a>";

						# When we hit the current section, go ahead and expand it as well
						if ($sibling->getId() == $this->section->getId())
						{
							if (count($this->section->getChildren()))
							{
								echo "<ul>";
								foreach($this->section->getChildren() as $child)
								{
									$name = View::escape($child->getName());
									echo "<li><a href=\"".BASE_URL."/sections/viewSection.php?section_id={$child->getId()}\">$name</a></li>\n";
								}
								echo "</ul>\n";
							}
						}
						echo "</li>\n";
					}
					echo "</ul>";
				}
				echo "</li>\n";
			}
			echo "</ul></li>\n";

			# Since we went ahead and expanded everything from the second to last ancestor on,
			# there's no reason to keep looping through the ancestors - we're done
			break;
		}
		else
		{
			# Just show a single ancestor
			echo "<li>$count : $targetCount <a href=\"".BASE_URL."/sections/viewSection.php?section_id={$section->getId()}\">$name</a></li>";
		}
	}

	echo "</ul></div>";
?>