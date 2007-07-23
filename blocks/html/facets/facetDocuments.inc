<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Facet $this->facet
 */
?>
<div class="interfaceBox">
	<div class="titleBar"><?php echo View::escape($this->facet->getName()); ?></div>
	<ul><?php
			foreach($this->facet->getDocuments() as $document)
			{
				$title = View::escape($document->getTitle());
				echo "<li><a href=\"{$document->getURL()}\">$title</a></li>\n";
			}
		?>
	</ul>
</div>
