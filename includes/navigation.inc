<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
	function renderMenu($sectionList)
	{
		echo "<ul>";
		foreach($sectionList as $section)
		{
			echo "<li><a href=\"".BASE_URL."/documents/viewDocument.php?document_id={$section->getDocument_id()}\">";
			echo View::sanitizeString($section->getName());
			echo '</a>';
			if (count($section->getChildren())) { renderMenu($section->getChildren()); }
			echo '</li>';
		}
		echo "</ul>";
	}
?>
<div class="menuBar">
<?php
	renderMenu(new SectionList(array('parent_id'=>1),"placement"));
?>
</div>