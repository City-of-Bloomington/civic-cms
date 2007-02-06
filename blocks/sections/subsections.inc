<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
/*
	$this->section
*/
?>
<div class="interfaceBox">
	<div class="titleBar">Sub Sections</div>
	<ul><?php
			foreach($this->section->getChildren() as $section)
			{
				echo "<li><a href=\"".BASE_URL."/documents/viewDocument.php?document_id={$this->section->getDocument_id()}\">";
				echo View::sanitizeString($section->getName());
				echo "</a></li>";
			}
		?>
	</ul>
</div>