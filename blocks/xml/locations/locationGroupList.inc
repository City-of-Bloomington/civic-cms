<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param LocationGroupList $this->locationGroupList
 */
?>
<locationGroups>
<?php
	foreach($this->locationGroupList as $group)
	{
		$name = View::escape($group->getName());
		echo "
		<locationGroup id=\"{$group->getId()}\">
			<name>$name</name>
		</locationGroup>
		";
	}
?>
</locationGroups>
