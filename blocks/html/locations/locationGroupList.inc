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
		<button type="button" class="addSmall" onclick="document.location.href='<?php echo BASE_URL; ?>/locations/addLocationGroup.php';">Add</button>
		Location Groups
	</div>
	<ul><?php
			foreach($this->locationGroupList as $locationGroup)
			{
				echo "
				<li><button type=\"button\" class=\"editSmall\" onclick=\"document.location.href='".BASE_URL."/locations/updateLocationGroup.php?id={$locationGroup->getId()}';\">Edit</button>
					$locationGroup</li>
				";
			}
		?>
	</ul>
</div>
