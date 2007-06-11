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

	<tr><td><label for="location-name" class="required">Name</label></td>
		<td><input name="location[name]" id="location-name" value="<?php echo $this->location->getName(); ?>" /></td></tr>
	<tr><td><label for="location-address" class="required">Address</label></td>
		<td><input name="location[address]" id="location-address" value="<?php echo $this->location->getAddress(); ?>" /></td></tr>
	<tr><td><label for="location-latitude">Latitude</label></td>
		<td><input name="location[latitude]" id="location-latitude" value="<?php echo $this->location->getLongitude(); ?>" /></td></tr>
	<tr><td><label for="location-longitude">Longitude</label></td>
		<td><input name="location[longitude]" id="location-longitude" value="<?php echo $this->location->getLongitude(); ?>" /></td></tr>
	<tr><td colspan="2">
			<label for="location-description" class="required">Description</label>
			<textarea name="location[description]" id="location-description" rows="3" cols="60"><?php echo $this->location->getDescription(); ?></textarea>
	</td></tr>

	</table>
</fieldset>
<fieldset><legend>Directions</legend>
	<?php
		include APPLICATION_HOME.'/html/editors/fckeditor/FCKeditor.php';
		$FCKeditor = new FCKeditor("directions");
		$FCKeditor->BasePath = BASE_URL.'/editors/fckeditor/';
		$FCKeditor->ToolbarSet = 'Custom';

		$FCKeditor->Value = $this->location->getDirections();

		$FCKeditor->create();
	?>
</fieldset>
<fieldset><legend>Submit</legend>
	<button type="submit" class="submit">Submit</button>
	<button type="button" class="cancel" onclick="document.location.href='<?php echo BASE_URL; ?>/locations';">Cancel</button>
</fieldset>
</form>
