<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Location $this->location
 */
$name = View::escape($this->location->getName());
$address = View::escape($this->location->getAddress());
$phone = View::escape($this->location->getPhone());
$description = View::escape($this->location->getDescription());
$website = '';
if ($this->location->getWebsite())
{
	$website = new URL($this->location->getWebsite());
	$website = "<a href=\"$website\">$website</a>";
}

$n = addslashes($name);
$directionsURL = "http://maps.google.com/?q=to:$n@{$this->location->getLatitude()},{$this->location->getLongitude()}";
$directions = "Get Directions: <a href=\"$directionsURL\" onclick=\"window.open('$directionsURL');return false;\">To $name</a>";

$class = $this->location->isHandicapAccessible() ? 'class="handicap_accessible"' : '';

echo "
<h1 $class>$name</h1>
<table>
<tr><th>Address</th>
	<td>$address</td></tr>
<tr><th>Phone Number</th>
	<td>$phone</td></tr>
<tr><th>Description</th>
	<td>$description</td></tr>
<tr><th>Website</th>
	<td>$website</td></tr>
<tr><th>Directions</th>
	<td>$directions</td></tr>
</table>
";
echo WikiMarkup::parse($this->location->getContent());

if (defined('GOOGLE_API_KEY'))
{
?>
<div id="location_map">
</div>
<script src="http://maps.google.com/maps?file=api&amp;v=2.77&amp;key=<?php echo GOOGLE_API_KEY; ?>" type="text/javascript"></script>
<script type="text/javascript">
	var point = new GLatLng(<?php echo $this->location->getLatitude(); ?>,<?php echo $this->location->getLongitude(); ?>);
	<?php
		# We need to add some more slashes to stuff we're putting inside of JavaScript strings for the map
		$d = addslashes(str_replace(array("\r\n","\n","\r"),' ',$description));
		$directions = "Get Directions: <a href=\"$directionsURL\" onclick=\"window.open(\'$directionsURL\');return false;\">To $name</a>";
	?>
	var info = '<?php echo "<h3 style=\"width:200px\">$n</h3><p style=\"width:200px\">$d</p><p>$directions</p>"; ?>';

	var map = new GMap2(document.getElementById("location_map"));
	var infoWindowMaxWidth = 350;

	function loadMap()
	{
		if (GBrowserIsCompatible())
		{
			// Create map and add controls
			map.addControl(new GSmallMapControl());
			map.addControl(new GMapTypeControl());
			map.setCenter(new GLatLng(39.167119,-86.533800), 12);
			map.setMapType(G_HYBRID_MAP);

			map.addOverlay(createMarker(point,info));

			var bounds = new GLatLngBounds();
			bounds.extend(point);
			map.setCenter(bounds.getCenter(),map.getBoundsZoomLevel(bounds));
		}
	}

	//Create a marker with your own icon or with default icon (where icon = null)
	function createMarker(point, info, icon)
	{
		if (icon == null) { var marker = new GMarker(point); }
		else { var marker = new GMarker(point, icon); }
		GEvent.addListener( marker, "click", function() { marker.openInfoWindowHtml(info,{'maxWidth':infoWindowMaxWidth}); });
		return marker;
	}

	setTimeout('loadMap()',500);
</script>
<?php
} # End of If checking for GOOGLE_API_KEY
?>
<script>
	var gaJsHost = (("https:" == document.location.protocol) ? "https://ssl." : "http://www.");
	document.write(unescape("%3Cscript src='" + gaJsHost + "google-analytics.com/ga.js' type='text/javascript'%3E%3C/script%3E"));
	try {
		var pageTracker = _gat._getTracker("UA-9224894-1");
		pageTracker._trackPageview();
	}
	catch(err) {
	}
</script>
