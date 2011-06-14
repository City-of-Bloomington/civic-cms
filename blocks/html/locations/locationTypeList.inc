<?php
/**
 * @copyright Copyright (C) 2007-2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
?>
<div class="interfaceBox">
	<h2>
		<a class="addSmall button" href="<?php echo BASE_URL; ?>/locations/addLocationType.php">Add</a>
		Location Types
	</h2>
	<ul><?php
			foreach($this->locationTypeList as $locationType)
			{
				echo "
				<li><a class=\"editSmall button\" href=\"".BASE_URL."/locations/updateLocationType.php?id={$locationType->getId()}\">Edit</a>
					$locationType</li>
				";
			}
		?>
	</ul>
</div>
