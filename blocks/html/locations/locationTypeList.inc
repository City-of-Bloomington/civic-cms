<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
?>
<div class="interfaceBox">
	<h1>
		<button type="button" class="addSmall" onclick="document.location.href='<?php echo BASE_URL; ?>/locations/addLocationType.php';">Add</button>
		Location Types
	</h1>
	<ul><?php
			foreach($this->locationTypeList as $locationType)
			{
				echo "
				<li><button type=\"button\" class=\"editSmall\" onclick=\"document.location.href='".BASE_URL."/locations/updateLocationType.php?id={$locationType->getId()}';\">Edit</button>
					$locationType</li>
				";
			}
		?>
	</ul>
</div>
