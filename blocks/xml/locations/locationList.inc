<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param LocationGroup $this->locationList
 */
?>
<locations>
<?php
	if (isset($this->locationList))
	{
		foreach($this->locationList as $location)
		{
			$name = View::escape($location->getName());
			$address = View::escape($location->getAddress());
			$description = View::escape($location->getDescription());

			$type = View::escape($location->getLocationType()->getType());

			$distance = '';
			if (isset($_GET['latitude']) && isset($_GET['longitude'])) {
				$distance = $location->getDistance($_GET['latitude'],$_GET['longitude']);
			}

			echo "
			<location id=\"{$location->getId()}\">
				<name>$name</name>
				<type>$type</type>
				<address>$address</address>
				<description>$description</description>
				<latitude>{$location->getLatitude()}</latitude>
				<longitude>{$location->getLongitude()}</longitude>
				<distance units=\"miles\">$distance</distance>
			</location>
			";
		}
	}
?>
</locations>
