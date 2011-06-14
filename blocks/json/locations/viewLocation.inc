<?php
/**
 * @copyright 2010 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Location $this->location
 */
$l = array('id'=>$this->location->getId(),
			'name'=>$this->location->getName(),
			'address'=>$this->location->getAddress(),
			'description'=>$this->location->getDescription(),
			'type'=>$this->location->getLocationType()->getType(),
			'latitude'=>$this->location->getLatitude(),
			'longitude'=>$this->location->getLongitude(),
			'content'=>WikiMarkup::parse($this->location->getContent())
			);
echo json_encode($l);

