<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Section $this->section
 */
?>
<div class="interfaceBox">
	<div class="titleBar">Documents</div>
	<ul>
	<?php
		foreach($this->section->getDocuments() as $document)
		{
			echo "<li><a href=\"{$document->getURL()}\">{$document->getId()}</a></li>";
		}
	?>
	</ul>
</div>
