<div class="interfaceBox">
	<div class="titleBar">
		<a href="<?php echo BASE_URL; ?>/locations">Locations</a>
	</div>
	<?php
	/**
	* @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
	* @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
	* @author Cliff Ingham <inghamn@bloomington.in.gov>
	*/
	include_once APPLICATION_HOME.'/includes/js/tree.inc';

	$list = new LocationGroupList();
	$list->find();
	echo '<ul class="expandable">';
	foreach($list as $group)
	{
		$name = View::escape($group->getName());
		echo "<li><a href=\"{$group->getURL()}\">$name</a>";
		if (count($group->getLocations()))
		{
			echo '<ul>';
			foreach($group->getLocations() as $location)
			{
				$name = View::escape($location->getName());
				echo "<li class=\"closed\"><a href=\"{$location->getURL()}\">$name</a></li>";
			}
			echo '</ul>';
		}
		echo "</li>";
	}
	echo '</ul>';
?>
</div>
