<?php
/**
 * @copyright Copyright (C) 2007-2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
echo '<h2>Most Popular Documents by Department</h2>';

$list = new DepartmentList();
$list->find();
foreach($list as $department)
{
	$hits = DocumentAccessLog::getTopDepartmentDocuments($department);
	if (count($hits))
	{
		$name = View::escape($department->getName());
		echo "
		<h3>$name</h3>
		<table>
		<tr><th>ID</th><th>Document</th><th>Hits</th></tr>
		";

		foreach($hits as $hit)
		{
			$title = View::escape($hit['document']->getTitle());
			echo "
			<tr><th>$hit[document_id]</th>
				<td><a href=\"{$hit['document']->getURL()}\">$title</a></td>
				<td>$hit[count]</td>
			</tr>
			";
		}
		echo '</table>';
	}
}
