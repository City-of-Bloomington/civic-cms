<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
?>
<h2>KML for Google Earth and Google Maps</h2>
<p>These links provide live location data from our website in KML format.</p>
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