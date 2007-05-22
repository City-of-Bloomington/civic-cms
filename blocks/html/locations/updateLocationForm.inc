<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Location $this->location
 */
?>
<h1>Update Location</h1>
<form method="post" action="<?php echo $_SERVER['PHP_SELF']; ?>">
<fieldset><legend>Location Info</legend>
	<input name="id" type="hidden" value="<?php echo $this->location->getId(); ?>" />
	<table>

	<tr><td><label for="location-name">Name</label></td>
		<td><input name="location[name]" id="location-name" value="<?php echo $this->location->getName(); ?>" /></td></tr>
	<tr><td><label for="location-latitude">Latitude</label></td>
		<td><input name="location[latitude]" id="location-latitude" value="<?php echo $this->location->getLongitude(); ?>" /></td></tr>
	<tr><td><label for="location-longitude">Longitude</label></td>
		<td><input name="location[longitude]" id="location-longitude" value="<?php echo $this->location->getLongitude(); ?>" /></td></tr>

	</table>

	<button type="submit" class="submit">Submit</button>
	<button type="button" class="cancel" onclick="document.location.href='<?php echo BASE_URL; ?>/locations';">Cancel</button>
</fieldset>
</form>