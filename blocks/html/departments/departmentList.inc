<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param DepartmentList $this->departmentList
 */
?>
<h1><?php if (userHasRole('Administrator')) { echo "<button type=\"button\" class=\"addSmall\" onclick=\"document.location.href='".BASE_URL."/departments/addDepartment.php';\">Add</button>"; } ?>
	Departments</h1>
<ul>
<?php
	foreach($this->departmentList as $department)
	{
		echo "<li>";
		if (userHasRole('Administrator')) { echo "<button type=\"button\" class=\"editSmall\" onclick=\"document.location.href='".BASE_URL."/departments/updateDepartment.php?department_id={$department->getId()}';\">Edit</button>"; }
		echo View::escape($department->getName())."</li>";
	}
?>
</ul>
