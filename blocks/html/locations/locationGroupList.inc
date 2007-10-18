<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param LocationGroupList $this->locationGroupList
 */
?>
<div class="interfaceBox">
	<div class="titleBar">
		<?php
			if (userHasRole(array('Administrator','Webmaster')))
			{
				echo "<button type=\"button\" class=\"addSmall\" onclick=\"document.location.href='".BASE_URL."/locations/addLocationGroup.php';\">Add</button>";
			}
		?>
		Location Groups
	</div>
	<ul><?php
			foreach($this->locationGroupList as $locationGroup)
			{
				$name = View::escape($locationGroup->getName());

				if (isset($_SESSION['USER']) && $locationGroup->permitsEditingBy($_SESSION['USER']))
				{
					$buttons = "
					<button type=\"button\" class=\"editSmall\" onclick=\"document.location.href='".BASE_URL."/locations/updateLocationGroup.php?id={$locationGroup->getId()}';\">Edit</button>
					<button type=\"button\" class=\"deleteSmall\" onclick=\"FRAMEWORK.deleteConfirmation('".BASE_URL."/locations/deleteLocationGroup.php?locationGroup_id={$locationGroup->getId()}');\">Delete</button>
					";
				}
				else { $buttons = ''; }

				echo "<li>$buttons $name</li>\n";
			}
		?>
	</ul>
</div>
