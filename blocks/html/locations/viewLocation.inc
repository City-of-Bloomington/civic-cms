<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Location $this->location
 */
	$name = View::escape($this->location->getName());
	$address = View::escape($this->location->getAddress());
	$description = View::escape($this->location->getDescription());

	echo "
	<h1>$name</h1>
	<p>$address</p>
	<p>$description></p>
	";
	echo WikiMarkup::parse($this->location->getContent());
?>
<div id="location_map">
</div>
<script src="http://maps.google.com/maps?file=api&amp;v=2.77&amp;key=ABQIAAAACqoQOZ2EAqg13jBR94AfexQNf7mhA6pY0zZO8gsdk0EdOTN8sxQDa2L0KB-dgEIEE-5Qas2VnQE6DQ" type="text/javascript"></script>
<script type="text/javascript">
	var point = new GLatLng(<?php echo $this->location->getLatitude(); ?>,<?php echo $this->location->getLongitude(); ?>);
	var info = '<h3 style="width:200px"><?php echo addslashes($name); ?></h3><p style="width:200px"><?php echo addslashes($description); ?></p>';

	var map = new GMap2(document.getElementById("location_map"));
	function loadMap()
	{
		if (GBrowserIsCompatible())
		{
			// Create map and add controls
			map.addControl(new GSmallMapControl());
			map.addControl(new GMapTypeControl());
			map.setCenter(new GLatLng(39.167119,-86.533800), 12);

			map.addOverlay(createMarker(point,info));
		}
	}

	//Create a marker with your own icon or with default icon (where icon = null)
	function createMarker(point, info, icon)
	{
		if (icon == null) { var marker = new GMarker(point); }
		else { var marker = new GMarker(point, icon); }
		GEvent.addListener(marker, "click", function() { marker.openInfoWindowHtml(info); });
		return marker;
	}

	setTimeout('loadMap()',500);
</script>
