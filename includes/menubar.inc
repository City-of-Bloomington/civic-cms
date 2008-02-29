<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
?>
<div id="topLevelSections">
<ul><li><a href="<?php echo BASE_URL; ?>">Home</a></li>
<?php
	#$sectionNodeList = new SectionNodeList(array('parent_id'=>1));
	#foreach($sectionNodeList as $node)
	$sectionList = new SectionList(array('parent_id'=>1));
	foreach($sectionList as $section)
	{
		#$section = $node->getSection();
		echo "<li><a href=\"".BASE_URL."/sections/viewSection.php?section_id={$section->getId()}\">";
		echo View::escape($section->getName());
		echo '</a></li>';
	}
?>
</ul>
</div>
