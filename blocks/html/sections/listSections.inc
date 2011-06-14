<div class="interfaceBox">
<?php
/**
 * @copyright Copyright (C) 2006-2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Section $this->section
 */
if (userHasRole(array('Administrator','Webmaster')))
{
	echo "
	<h2>
		Sections
		<a href=\"".BASE_URL."/sections/addSection.php\" class=\"addSmall button\">Add</a>
	</h2>
	";
}
else { echo "<h2><a href=\"".BASE_URL."/sections\">Sections</a></h2>"; }

if (isset($this->section))
{
	echo '<ul><li>';

	# Start with the given section
	$section = new Section($this->section->getId());
	$name = View::escape($section->getName());
	if (userHasRole(array('Administrator','Webmaster')))
	{
		echo "
		<a href=\"".BASE_URL."/sections/sectionInfo.php?section_id={$section->getId()}\">$name</a>
		<a class=\"info\" href=\"".BASE_URL."/sections/sectionInfo.php?section_id={$section->getId()}\">Info</a>
		<a class=\"view\" href=\"".BASE_URL."/sections/viewSection.php?section_id={$section->getId()}\">View</a>
		<ul class=\"mktree\">
		";
	}
	else
	{
		echo "
		<a href=\"{$section->getURL()}\">$name</a>
		<ul class=\"mktree\">
		";
	}

	listSections($section);

	echo "
		</ul>
		</li>
	</ul>
	";
}

/**
 * This fires off the JavaScript that turns an expandable UL into a tree
 * This library has a bug - it will freeze if the <li> elements are not on their
 * own line.  Make sure to put line breaks for each <li>
 */
include_once APPLICATION_HOME.'/includes/js/tree.inc';
function listSections($parent)
{
	foreach($parent->getChildNodes() as $node)
	{
		$section = $node->getSection();

		$name = View::escape($section->getName());
		if (userHasRole(array('Administrator','Webmaster')))
		{
			echo "
			<li class=\"liClosed\">
				<a href=\"".BASE_URL."/sections/sectionInfo.php?section_id={$section->getId()}\">$name</a>
				<a class=\"info\" href=\"".BASE_URL."/sections/sectionInfo.php?section_id={$section->getId()}\">Info</a>
				<a class=\"view\" href=\"".BASE_URL."/sections/viewSection.php?section_id={$section->getId()}\">View</a>
			";
		}
		else
		{
			echo "
			<li class=\"liClosed\">
				<a href=\"{$section->getURL()}\">$name</a>
			";
		}

		if ($section->hasChildren())
		{
			echo "<ul>";
			listSections($section);
			echo "</ul>";
		}

		echo "</li>";
	}
}
?>
</div>
