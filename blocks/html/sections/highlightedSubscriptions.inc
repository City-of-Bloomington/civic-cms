<?php
/**
 * @copyright Copyright (C) 2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param SectionList $this->sectionList
 */

?>
<div class="interfaceBox">
	<h1>Subscriptions</h1>
	<ul><?php
			foreach($this->sectionList as $section)
			{
				$name = View::escape($section->getName());
				echo "<li>$name</li>";
			}
		?>
	</ul>
</div>