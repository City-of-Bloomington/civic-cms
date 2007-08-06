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
		echo "<ul>";


		foreach($department->office as $office)
		{
			$url->parameters['location'] = urlencode($office['name']);
			$name = View::escape($office['name']);
			echo "<li><a href=\"$url\">$name</a><table>";
			foreach ($office->person as $person)
			{
				echo "
				<tr><td>{$person->name}, {$person->title}</td>
					<td>{$person->phone}</td>
					<td><a href=\"mailto:{$person->email}\">{$person->email}</td>
				</tr>
				";
			}
			echo "</table></li>";
		}
		echo "</ul>";
	}
	else
	{
		echo "<p>You must install the Directory web application to use this feature</p>";
	}
?>