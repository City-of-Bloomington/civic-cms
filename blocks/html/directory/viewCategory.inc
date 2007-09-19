<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param string $this->category
 */
	if (defined('DIRECTORY_WEBSERVICE'))
	{
		$this->category = urlencode($this->category);
		$category = new SimpleXMLElement(DIRECTORY_WEBSERVICE."/viewCategory.php?category={$this->category};format=xml",null,true);

		$url = new URL(BASE_URL.'/directory/viewDepartment.php');
		$url->parameters['category'] = $category['name'];

		$name = View::escape($category['name']);
		foreach($category->department as $department)
		{
			$url->parameters['department'] = $department['name'];

			$name = View::escape($department['name']);
			echo "<h1><a href=\"$url\">$name</a></h1>";

			foreach($department->office as $office)
			{
				$url->parameters['location'] = urlencode($office['name']);
				$name = View::escape($office['name']);
				echo "
				<h2><a href=\"$url\">$name</a></h2>
					<table>
					<tr><th>Name</th>
						<th>Title</th>
						<th>Phone</th>
						<th>Email</th>
					</tr>
				";
				foreach ($office->person as $person)
				{
					echo "
					<tr><td>{$person->name}</td>
						<td>{$person->title}</td>
						<td>{$person->phone}</td>
						<td><a href=\"mailto:{$person->email}\">{$person->email}</td>
					</tr>
					";
				}
				echo "</table>";
			}
		}
	}
	else
	{
		echo "<p>You must install the Directory web application to use this feature</p>";
	}
?>