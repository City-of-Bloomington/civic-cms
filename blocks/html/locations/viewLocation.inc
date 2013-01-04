<?php
/**
 * @copyright 2007-2013 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Location $this->location
 */
$name    = View::escape($this->location->getName());
$address = View::escape($this->location->getAddress());
$phone   = View::escape($this->location->getPhone());
$description = WikiMarkup::parse($this->location->getDescription());
$website = '';
if ($this->location->getWebsite()) {
	$website = new URL($this->location->getWebsite());
	$website = "<a href=\"$website\">$website</a>";
}

$n = addslashes($name);
$directionsURL = "http://maps.google.com/?q=to:$n@{$this->location->getLatitude()},{$this->location->getLongitude()}";
$directions = "Get Directions: <a href=\"$directionsURL\" onclick=\"window.open('$directionsURL');return false;\">To $name</a>";

$class = $this->location->isHandicapAccessible() ? 'class="handicap_accessible"' : '';

echo "<h1 $class>$name</h1><table>";
if ($address) {
	echo "<tr><th>Address</th><td>$address</td></tr>";
}
if ($phone) {
	echo "<tr><th>Phone Number</th><td>$phone</td></tr>";
}
if ($description) {
	echo "<tr><th>Description</th><td>$description</td></tr>";
}
if ($website) {
	echo "<tr><th>Website</th><td>$website</td></tr>";
}
if ($directions) {
	echo "<tr><th>Directions</th><td>$directions</td></tr>";
}
echo "</table>";
echo WikiMarkup::parse($this->location->getContent());

if (defined('GOOGLE_MAPS')) {
	$this->template->addToAsset('scripts', GOOGLE_MAPS);
	$this->template->addToAsset('scripts', BASE_URL.'/js/map.js');

	# We need to add some more slashes to stuff we're putting inside of JavaScript strings for the map
	$lat  = $this->location->getLatitude();
	$long = $this->location->getLongitude();
	$d = addslashes(str_replace(array("\r\n","\n","\r"),' ',$description));
	$directions = "Get Directions: <a href=\"$directionsURL\" onclick=\"window.open(\'$directionsURL\');return false;\">To $name</a>";
	$info = "<h3 style=\"width:200px\">$n</h3><p style=\"width:200px\">$d</p><p>$directions</p>";

	echo "
	<div id=\"location_map\"></div>
	<script type=\"text/javascript\">
		var points = [{
			latitude:$lat,
			longitude:$long,
			info: '$info'
		}];
	</script>
	";
}
