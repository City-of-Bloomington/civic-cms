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
<table>
<?php
	foreach($this->departmentList as $department)
	{
		$name = View::escape($department->getName());
		$address1 = View::escape($department->getAddress1());
		$phone = View::escape($department->getPhone());
		$email = View::escape($department->getEmail());
		echo "<tr>";
		if (userHasRole('Administrator')) { echo "<td><button type=\"button\" class=\"editSmall\" onclick=\"document.location.href='".BASE_URL."/departments/updateDepartment.php?department_id={$department->getId()}';\">Edit</button></td>"; }
		if ($department->getDocument_id())
		{
			$name = "<a href=\"".BASE_URL."/documents/viewDocument.php?document_id={$department->getDocument_id()}\">$name</a>";
		}
		echo "
			<td>$name</td>
			<td>$address1</td>
			<td>$phone</td>
			<td>$email</td>
		</tr>
		";
	}
?>
</table>
