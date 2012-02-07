<?php
/**
 * @copyright 2007-2009 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param LocationGroupList $this->locationGroupList
 */
?>
<div class="interfaceBox">
	<h2>
		<?php
			if (userHasRole(array('Administrator','Webmaster')))
			{
				echo "<a class=\"addSmall button\" href=\"".BASE_URL."/locations/addLocationGroup.php\">Add</a>";
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
					<a class=\"editSmall button\" href=\"".BASE_URL."/locations/updateLocationGroup.php?id={$locationGroup->getId()}\">Edit</a>
					<button type=\"button\" class=\"deleteSmall\" onclick=\"FRAMEWORK.deleteConfirmation('".BASE_URL."/locations/deleteLocationGroup.php?locationGroup_id={$locationGroup->getId()}');\">Delete</button>
					";
				}
				else { $buttons = ''; }

				$class = $locationGroup->isDefault() ? ' class="default"' : '';
				echo "
				<li$class>
					$buttons
					<a href=\"{$locationGroup->getURL()}\">$name</a>
				</li>
				";
			}
		?>
	</ul>
</div>
