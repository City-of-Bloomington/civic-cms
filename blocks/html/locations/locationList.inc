<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param LocationList $this->locationList
 * @param string $this->title
 */
?>
<div class="interfaceBox">
	<div class="titleBar">
		<button type="button" class="addSmall" onclick="document.location.href='<?php echo BASE_URL; ?>/locations/addLocation.php';">Add</button>
		<?php echo View::escape($this->title); ?>
	</div>
	<ul><?php
			foreach($this->locationList as $location)
			{
				$name = View::escape($location->getName());

				echo "
				<li><button type=\"button\" class=\"editSmall\" onclick=\"document.location.href='".BASE_URL."/locations/updateLocation.php?id={$location->getId()}';\">Edit</button>
					$name
				</li>
				";
			}
		?>
	</ul>
</div>
