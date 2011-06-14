<div class="interfaceBox">
	<h2>
		<a href="<?php echo BASE_URL; ?>/locations">Locations</a>
	</h2>
	<?php
	/**
	* @copyright Copyright (C) 2007-2008 City of Bloomington, Indiana. All rights reserved.
	* @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
	* @author Cliff Ingham <inghamn@bloomington.in.gov>
	*/
	include_once APPLICATION_HOME.'/includes/js/tree.inc';

	$list = new LocationGroupList();
	$list->find();
	echo '<ul class="mktree">';
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
				echo "<li><a href=\"{$location->getURL()}\">$name</a></li>";
			}
			echo '</ul>';
		}
		echo "</li>";
	}
	echo '</ul>';
?>
</div>
