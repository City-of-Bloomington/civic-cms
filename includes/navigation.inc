<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
?>
<div class="menuBar">
	<ul>
	<?php
		$sections = new SectionList(array('parent_id'=>1),"placement");
		foreach($sections as $section)
		{
			echo "<li><a href=\"".BASE_URL."/documents/viewDocument.php?document_id={$section->getDocument_id()}\">";
			echo View::sanitizeString($section->getName());
			if (count($section->getChildren()))
			{
				echo "<ul>";
				foreach($section->getChildren() as $child)
				{
					echo "<li><a href=\"".BASE_URL."/documents/viewDocument.php?document_id={$child->getDocument_id()}\">";
					echo View::sanitizeString($child->getName());
				}
				echo "</ul>";
			}
			echo "</a></li>";
		}
	?>
	</ul>
	<p><?php  ?></p>
</div>