<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param LocationGroup $this->locationGroup (optional)
 * @param Location $this->location (optional)
 */
?>
<div id="pageTitle">
	<div class="breadcrumbs">
	<?php
		if(isset($this->locationGroup))
		{
			$groupName = View::escape($this->locationGroup->getName());
			echo "
			<ul><li><a href=\"".BASE_URL."\">Home</a></li>
				<li><a href=\"".BASE_URL."/locations\">Locations</a></li>
				<li>$groupName</li>
			</ul>
			";
		}
		elseif (isset($this->location))
		{
			$locationName = View::escape($this->location->getName());
			foreach($this->location->getLocationGroups() as $group)
			{
				$groupName = View::escape($group->getName());
				echo "
				<ul><li><a href=\"".BASE_URL."\">Home</a></li>
					<li><a href=\"".BASE_URL."/locations\">Locations</a></li>
					<li><a href=\"{$group->getURL()}\">$groupName</a></li>
					<li>$locationName</li>
				</ul>
				";
			}
		}
		else
		{
			echo "
			<ul><li><a href=\"".BASE_URL."\">Home</a></li>
				<li>Locations</li>
			</ul>
			";
		}
	?>
	</div>
	<h1>
	<?php
		if (isset($locationName)) { echo $locationName; }
		elseif (isset($groupName)) { echo $groupName; }
		else { echo 'Locations'; }
	?>
	</h1>
</div>