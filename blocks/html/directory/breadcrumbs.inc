<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff ingham <inghamn@bloomington.in.gov>
 * @param string $this->category (optional)
 * @param string $this->department (optional)
 * @param string $this->location (optional)
 */
echo "
<div id=\"pageTitle\">
	<div class=\"breadcrumbs\">
	<ul><li><a href=\"".BASE_URL."/directory\">Departments</a></li>
	";
	if (isset($this->category)) { echo "<li><a href=\"".BASE_URL."/directory/viewCategory.php?category={$this->category}\">{$this->category}</a></li>"; }
	if (isset($this->department)) { echo "<li><a href=\"".BASE_URL."/directory/viewDepartment.php?category={$this->category};department={$this->department}\">{$this->department}</a></li>"; }
	if (isset($this->location)) { echo "<li><a href=\"".BASE_URL."/directory/viewLocation.php?category={$this->category};department={$this->department};location={$this->location}\">{$this->location}</a></li>"; }
	echo "
	</ul>
	</div>
	<h1>Directory</h1>
</div>
";
