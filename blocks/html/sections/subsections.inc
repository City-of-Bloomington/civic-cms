<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Section $this->section
 */
?>
<div class="interfaceBox">
	<div class="titleBar">Sub Sections</div>
	<ul><?php
			foreach($this->section->getChildren() as $section)
			{
				$name = View::escape($section->getName());
				echo "
				<li><a href=\"{$this->section->getDocument()->getURL()}\">$name</a></li>
				";
			}
		?>
	</ul>
</div>
