<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Section $this->section
 */
?>
<div class="widget">
	<h1>
	<?php
		echo View::escape($this->section->getName());
	?>
	</h1>
	<ul>
	<?php
		foreach($this->section->getChildren() as $section)
		{
			$name = View::escape($section->getName());
			echo "<li><a href=\"{$section->getURL()}\">$name</a></li>";
		}
	?>
	</ul>
</div>