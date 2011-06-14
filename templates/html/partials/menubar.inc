<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
?>
<div id="topLevelSections">
<ul><li class="home"><a href="<?php echo BASE_URL; ?>">Home</a></li>
<?php
	$sectionList = new SectionList(array('parent_id'=>1));
	foreach($sectionList as $section)
	{
		$name = View::escape($section->getName());
		$class = WikiMarkup::wikify($section->getName());
		echo "\t<li class=\"$class\"><a href=\"".BASE_URL."/sections/viewSection.php?section_id={$section->getId()}\">$name</a></li>\n";
	}
?>
</ul>
</div>
