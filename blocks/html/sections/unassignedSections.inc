<?php
/**
 * @copyright Copyright (C) 2007,2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param SectionList $this->sectionList
 */
if (count($this->sectionList)>1)
{
	echo "
	<div class=\"interfaceBox\">
		<h1>Unassigned Sections</h1>
		<p>These Sections have not been assigned any parents.
			You must assign them a parent to get them to show up in the site.</p>
		<ul>
	";

	foreach($this->sectionList as $section)
	{
		if ($section->getId() != 1)
		{
			$name = View::escape($section->getName());
			echo "
			<li><a href=\"".BASE_URL."/sections/viewSection.php?section_id={$section->getId()}\">$name</a>
				<a class=\"info\" href=\"".BASE_URL."/sections/sectionInfo.php?section_id={$section->getId()}\">Info</a>
				<a class=\"view\" href=\"".BASE_URL."/sections/viewSection.php?section_id={$section->getId()}\">View</a>
			</li>
			";
		}
	}

	echo "
		</ul>
	</div>
	";

}
