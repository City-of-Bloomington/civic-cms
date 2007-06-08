<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param string $this->username
 */
	# Get the info from Directory
	$user = new SimpleXMLElement("http://isotope.bloomington.in.gov/directory/viewPerson.php?uid={$this->username};format=xml",null,true);

	echo "
	<table id=\"details\">
	<tr><th><img src=\"{$user->photo['src']}\" /></th>
		<td><h1>{$user->name}</h1>
			<h3>{$user->title}</h3>
			<h3>{$user->department}</h3>
			<h3>{$user->businessCategory}</h3>
		</td></tr>
	";
	foreach($user->phoneNumbers as $phone)
	{
		echo "
		<tr><th>{$phone->label}</th>
			<td>{$phone->number}</td></tr>
		";
	}
	echo "
	<tr><th>Fax</th>
		<td>{$user->fax}</td></tr>
	<tr><th>Delivery Office</th>
		<td>{$user->deliveryOffice}</td></tr>
	<tr><th>Email</th>
		<td><a href=\"mailto:{$user->email}\">{$user->email}</a></td></tr>
	</table>
	";
?>