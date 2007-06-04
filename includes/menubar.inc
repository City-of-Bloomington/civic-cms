<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
?>
<div class="menuBar">
<ul>
<?php
	#$sectionNodeList = new SectionNodeList(array('parent_id'=>1));
	#foreach($sectionNodeList as $node)
	$sectionList = new SectionList(array('parent_id'=>1));
	foreach($sectionList as $section)
	{
		#$section = $node->getSection();
		echo "<li><a href=\"".BASE_URL."/documents/viewDocument.php?document_id={$section->getDocument_id()}\">";
		echo View::escape($section->getName());
		echo '</a></li>';
	}
?>
</ul>
</div>
