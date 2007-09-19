<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param string $this->category
 * @param string $this->department
 * @param string $this->location
 */
	if (defined('DIRECTORY_WEBSERVICE'))
	{
		$office = new SimpleXMLElement(DIRECTORY_WEBSERVICE."/viewLocation.php?category={$this->category};department={$this->department};location={$this->location};format=xml",null,true);
		echo "
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
	else
	{
		echo "<p>You must install the Directory web application to use this feature</p>";
	}
?>