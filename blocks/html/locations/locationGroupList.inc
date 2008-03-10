<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param LocationGroupList $this->locationGroupList
 */
?>
<div class="interfaceBox">
	<h2>
		<?php
			if (userHasRole(array('Administrator','Webmaster')))
			{
				echo "<a class=\"addSmall\" href=\"".BASE_URL."/locations/addLocationGroup.php\">Add</a>";
			}
		?>
		Location Groups
	</h2>
	<ul><?php
			foreach($this->locationGroupList as $locationGroup)
			{
				$name = View::escape($locationGroup->getName());

				if (isset($_SESSION['USER']) && $locationGroup->permitsEditingBy($_SESSION['USER']))
				{
					$buttons = "
					<a class=\"editSmall\" href=\"".BASE_URL."/locations/updateLocationGroup.php?id={$locationGroup->getId()}\">Edit</a>
					<button type=\"button\" class=\"deleteSmall\" onclick=\"FRAMEWORK.deleteConfirmation('".BASE_URL."/locations/deleteLocationGroup.php?locationGroup_id={$locationGroup->getId()}');\">Delete</button>
					";
				}
				else { $buttons = ''; }

				echo "<li>$buttons $name</li>\n";
			}
		?>
	</ul>
</div>
