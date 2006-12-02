<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
?>
<div class="menuBar">
	<ul>
	<?php
		$sections = new SectionList(array('parent_id'=>1));
		foreach($sections as $section)
		{
			echo "<li><a href=\"".BASE_URL."/sections/viewSection.php?section_id={$section->getId()}\">";
			echo View::sanitizeString($section->getName());
			echo "</a></li>";
		}
	?>
	</ul>
</div>