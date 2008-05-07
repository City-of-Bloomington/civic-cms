<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
?>
<h2>KML for Google Earth and Google Maps</h2>
<p>KML is a file format that tells a map application how to display geographical
information.  Paste a KML address into an application, such as Google Earth,
AutoCAD, or Yahoo Pipes, and the application will read the file from our server
and display the information as a map.  Once saved, your application should identify
the most current map data on our website each time you open it.</p>
<table>
<?php
	$list = new LocationGroupList();
	$list->find();
	foreach($list as $group)
	{
		$name = View::escape($group->getName());
		$url = BASE_URL.'/locations?format=kml;locationGroup_id='.$group->getId();
		echo "<tr><th>$name</th><td><a href=\"$url\">$url</a></td></tr>";
	}
?>
</table>