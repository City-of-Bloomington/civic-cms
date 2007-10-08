<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param LocationGroup $this->locationGroup (optional)
 * @param Location $this->location (optional)
 */
?>
<div id="breadcrumbs">
<ul><li><a href="<?php echo BASE_URL; ?>">Home</a></li>
	<li><a href="<?php echo BASE_URL; ?>/locations">Locations</a></li>
	<?php
		if(isset($this->locationGroup))
		{
			$name = View::escape($this->locationGroup->getName());
			echo "<li><a href=\"".BASE_URL."/locations?locationGroup_id={$this->locationGroup->getId()}\">$name</a></li>";
		}

		if (isset($this->location))
		{
			$name = View::escape($this->location->getName());
			echo "<li><a href=\"".BASE_URL."/locations?location_id={$this->location->getId()}\">$name</a></li>";
		}
	?>
</ul>
</div>
