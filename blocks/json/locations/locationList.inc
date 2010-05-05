<?php
/**
 * @copyright 2010 City of Bloomington, Indiana
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param LocationGroup $this->locationList
 */
$locations = array();
foreach($this->locationList as $location) {
	$l = array('id'=>$location->getId(),
				'name'=>$location->getName(),
				'address'=>$location->getAddress(),
				'description'=>$location->getDescription(),
				'type'=>$location->getLocationType()->getType(),
				'latitude'=>$location->getLatitude(),
				'longitude'=>$location->getLongitude());

	if (isset($_GET['latitude']) && isset($_GET['longitude'])) {
		$l['distance'] = $location->getDistance($_GET['latitude'],$_GET['longitude']);
	}
	$locations[] = $l;
}
echo json_encode($locations);