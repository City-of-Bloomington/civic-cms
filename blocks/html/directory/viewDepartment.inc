<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param string $this->category
 * @param string $this->department
 */
	if (defined('DIRECTORY_WEBSERVICE'))
	{
		$this->category = urlencode($this->category);
		$this->department = urlencode($this->department);

		$department = new SimpleXMLElement(DIRECTORY_WEBSERVICE."/viewDepartment.php?category={$this->category};department={$this->department};format=xml",null,true);

		$url = new URL(BASE_URL.'/directory/viewLocation.php');
		$url->parameters['category'] = $this->category;
		$url->parameters['department'] = $department['name'];

		$name = View::escape($department['name']);


		foreach($department->office as $office)
		{
			$url->parameters['location'] = urlencode($office['name']);
			$name = View::escape($office['name']);
			echo "
			<h1><a href=\"$url\">$name</a></h1>
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
	else
	{
		echo "<p>You must install the Directory web application to use this feature</p>";
	}
?>