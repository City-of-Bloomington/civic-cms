<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param SectionList $this->sectionList
 */
	if (count($this->sectionList)>1)
	{
		echo "
		<div class=\"interfaceBox\">
			<div class=\"titleBar\">Unassigned Sections</div>
			<p>These Sections have not been assigned any parents.
				You must assign them a parent to get them to show up in the site.</p>
			<ul>
		";

		foreach($this->sectionList as $section)
		{
			if ($section->getId() != 1)
			{
				echo "<li><a href=\"".BASE_URL."/sections/viewSection.php?section_id={$section->getId()}\">{$section->getName()}</a></li>";
			}
		}

		echo "
			</ul>
		</div>
		";

	}
?>