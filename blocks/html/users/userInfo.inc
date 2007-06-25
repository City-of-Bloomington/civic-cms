<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param string $this->username
 */
	# Get the info from Directory
	$user = new SimpleXMLElement("http://isotope.bloomington.in.gov/directory/viewPerson.php?uid={$this->username};format=xml",null,true);

	$name = View::escape($user->name);
	$title = View::escape($user->title);
	$department = View::escape($user->department);
	$businessCategory = View::escape($user->businessCategory);
	echo "
	<table id=\"details\">
	<tr><th><img src=\"{$user->photo['src']}\" /></th>
		<td><h1>$name</h1>
			<h3>$title</h3>
			<h3>$department</h3>
			<h3>$businessCategory</h3>
		</td></tr>
	";
	foreach($user->phoneNumbers as $phone)
	{
		$label = View::escape($phone->label);
		$number = View::escape($phone->number);
		echo "
		<tr><th>$label</th>
			<td>$number</td></tr>
		";
	}


	$fax = View::escape($user->fax);
	$deliveryOffice = View::escape($user->deliveryOffice);
	$email = View::escape($user->email);
	echo "
	<tr><th>Fax</th>
		<td>$fax</td></tr>
	<tr><th>Delivery Office</th>
		<td>$deliveryOffice</td></tr>
	<tr><th>Email</th>
		<td><a href=\"mailto:$email\">$email</a></td></tr>
	</table>
	";
?>