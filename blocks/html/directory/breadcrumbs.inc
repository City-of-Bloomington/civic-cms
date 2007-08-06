<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff ingham <inghamn@bloomington.in.gov>
 * @param string $this->category
 * @param string $this->department (optional)
 * @param string $this->location (optional)
 */
	echo "
	<div class=\"breadcrumbs\">
		<a href=\"".BASE_URL."/directory\">Departments</a> &gt;
		<a href=\"".BASE_URL."/directory/viewCategory.php?category={$this->category}\">{$this->category}</a> &gt;
	";
	if (isset($this->department)) { echo "<a href=\"".BASE_URL."/directory/viewDepartment.php?category={$this->category};department={$this->department}\">{$this->department}</a> &gt;"; }
	if (isset($this->location)) { echo "<a href=\"".BASE_URL."/directory/viewLocation.php?category={$this->category};department={$this->department};location={$this->location}\">{$this->location}</a>"; }
	echo "
	</div>
	";
?>