<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param LocationGroup $this->locationGroup (optional)
 * @param Location $this->location (optional)
 */
?>
<div id="breadcrumbs">
<?php
	if(isset($this->locationGroup))
	{
		$name = View::escape($this->locationGroup->getName());
		echo "
		<ul><li><a href=\"".BASE_URL."\">Home</a></li>
			<li><a href=\"".BASE_URL."/locations\">Locations</a></li>
			<li><a href=\"{$this->locationGroup->getURL()}\">$name</a></li>
		</ul>
		";
	}
	elseif (isset($this->location))
	{
		$location = View::escape($this->location->getName());
		foreach($this->location->getLocationGroups() as $group)
		{
			$groupName = View::escape($group->getName());
			echo "
			<ul><li><a href=\"".BASE_URL."\">Home</a></li>
				<li><a href=\"".BASE_URL."/locations\">Locations</a></li>
				<li><a href=\"{$group->getURL()}\">$groupName</a></li>
				<li><a href=\"{$this->location->getURL()}\">$location</a></li>
			</ul>
			";
		}
	}
	else
	{
		echo "
		<ul><li><a href=\"".BASE_URL."\">Home</a></li>
			<li><a href=\"".BASE_URL."/locations\">Locations</a></li>
		</ul>
		";
	}
?>
</div>
