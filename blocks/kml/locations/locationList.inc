<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param LocationList $this->locationList
 * @param string $this->title
 * @param LocationGroup $this->locationGroup
 */
	if (isset($this->locationList))
	{
		$title = View::escape($this->title);
		$description = isset($this->locationGroup) ? View::escape(strip_tags($this->locationGroup->getDescription())) : '';
		echo "
		<Folder>
			<name>$title</name>
			<description>$description</description>
		";
		foreach($this->locationList as $location)
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
		echo "
		</Folder>
		";
	}
?>