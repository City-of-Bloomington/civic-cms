<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
$list = new LocationGroupList();
$list->find();
foreach($list as $group)
{
	$title = View::escape($group->getName());
	$description = View::escape(strip_tags($group->getDescription()));
	echo "
	<Folder>
		<name>$title</name>
		<description>$description</description>
	";
	foreach($group->getLocations() as $location)
	{
		if ($location->getLatitude() && $location->getLongitude())
		{
			$name = View::escape($location->getName());
			$address = View::escape($location->getAddress());
			$description = View::escape($location->getDescription());

			$type = View::escape($location->getLocationType()->getType());

			echo "
			<Placemark>
				<name>$name</name>
				<description>$description</description>
				<Point>
					<coordinates>{$location->getLongitude()},{$location->getLatitude()}</coordinates>
				</Point>
			</Placemark>
			";
		}
	}
	echo "</Folder>";
}