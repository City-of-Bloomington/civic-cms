<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
?>
<div class="interfaceBox">
	<h1>
		<a class="addSmall" href="<?php echo BASE_URL; ?>/locations/addLocationType.php">Add</a>
		Location Types
	</h1>
	<ul><?php
			foreach($this->locationTypeList as $locationType)
			{
				echo "
				<li><a class=\"editSmall\" href=\"".BASE_URL."/locations/updateLocationType.php?id={$locationType->getId()}\">Edit</a>
					$locationType</li>
				";
			}
		?>
	</ul>
</div>
