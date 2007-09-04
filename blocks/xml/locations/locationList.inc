<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param LocationGroup $this->locationGroup
 */
?>
<locations>
<?php
	if (isset($this->locationGroup)) { $list = new LocationList(array('locationGroup_id'=>$this->locationGroup->getId())); }
	else
	{
		$list = new LocationList();
		$list->find();
	}
	foreach($list as $location)
	{
		$name = View::escape($location->getName());
		$address = View::escape($location->getAddress());
		$description = View::escape($location->getDescription());

		$type = View::escape($location->getLocationType()->getType());

		echo "
		<location id=\"{$location->getId()}\">
			<name>$name</name>
			<type>$type</type>
			<address>$address</address>
			<description>$description</description>
			<latitude>{$location->getLatitude()}</latitude>
			<longitude>{$location->getLongitude()}</longitude>
		</location>
		";
	}
?>
</locations>
