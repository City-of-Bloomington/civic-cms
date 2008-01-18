<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param LocationList $this->locationList
 * @param string $this->title
 * @param LocationGroup $this->locationGroup
 */
?>
<h1>
	<button type="button" class="kml" onclick="document.location.href='<?php echo BASE_URL; ?>/locations/?format=kml';">Locations KML</button>
	Locations
</h1>
<p>Use this feature to find locations grouped together into categories, such as City Facilities or Historic Sites.
Using GoogleMap technology, you can find the position of different locations all across the city,
as well as find driving directions, and information specific to a certain site.</p>
<form method="get" action="<?php echo $_SERVER['PHP_SELF']; ?>">
<fieldset>
	<select name="locationGroup_id" onchange="this.form.submit();">
		<option value="">Choose a category</option>
		<option value=""></option>
	<?php
		$list = new LocationGroupList();
		$list->find();
		foreach($list as $group)
		{
			$name = View::escape($group->getName());

			if (isset($this->locationGroup) && $this->locationGroup->getId()==$group->getId()) { $selected = 'selected="selected"'; }
			else { $selected = ''; }

			echo "<option value=\"{$group->getId()}\" $selected>$name</option>\n";
		}
		$selected = $this->title=='Other' ? 'selected="selected"' : '';
		echo "<option value=\"0\" $selected>Other</option>";
	?>
	</select>
</fieldset>
</form>
<?php if(isset($this->locationList)) { ?>
<div class="interfaceBox" id="location_list">
	<div class="titleBar">
		<?php
			$return_url = "http://$_SERVER[SERVER_NAME]$_SERVER[REQUEST_URI]";

			if (userHasRole(array('Administrator','Webmaster','Content Creator')))
			{
				$add_url = new URL(BASE_URL.'/locations/updateLocation.php');
				$add_url->return_url = $return_url;
				echo "<button type=\"button\" class=\"addSmall\" onclick=\"document.location.href='$add_url';\">Add</button>";
			}

			$url = new URL(BASE_URL.'/locations');
			$url->format = 'kml';
			$url->locationGroup_id = isset($this->locationGroup) ? $this->locationGroup->getId() : 0;
			$title = View::escape($this->title);
			echo "<button type=\"button\" class=\"kml\" onclick=\"document.location.href='$url';\">$title KML</button>";

			echo $name;
		?>
	</div>
	<ul><?php
			$points = array();
			$info = array();
			foreach($this->locationList as $location)
			{
				$name = View::escape($location->getName());
				$description = View::escape($location->getDescription());

				# Check if the installation has a Google Maps Key
				# Make sure the location has Latitude and Longitude before trying to map it
				if (defined('GOOGLE_MAP_KEY') && $location->getLatitude() && $location->getLongitude())
				{
					$points[] = "new GLatLng({$location->getLatitude()},{$location->getLongitude()})";

					$n = addslashes($name);
					$d = addslashes(str_replace(array("\r\n","\n","\r"),' ',$description));

					$title = "<h3 style=\"width:200px\">$n</h3>";
					$desc = "<p style=\"width:200px\">$d</p>";
					$directions = "<p>Get Directions: <a href=\"http://maps.google.com/?q=to:$n@{$location->getLatitude()},{$location->getLongitude()}\">To Here</a></p>";
					$info[] = "'{$title}{$desc}{$directions}'";

					$i = count($points) - 1;
					$mapButton = "<a href=\"#\" onclick=\"popup($i)\">Reveal In Map</a>";
				}
				else { $mapButton = ''; }


				if (isset($_SESSION['USER']) && $location->permitsEditingBy($_SESSION['USER']))
				{
					$edit_url = new URL(BASE_URL.'/locations/updateLocation.php');
					$edit_url->location_id = $location->getId();
					$edit_url->return_url = $return_url;
					$editButton = "<button type=\"button\" class=\"editSmall\" onclick=\"document.location.href='$edit_url';\">Edit</button>";

					$delete_url = new URL(BASE_URL.'/locations/deleteLocation.php');
					$delete_url->location_id = $location->getId();
					$delete_url->return_url = $return_url;
					$deleteButton = "<button type=\"button\" class=\"deleteSmall\" onclick=\"FRAMEWORK.deleteConfirmation('$delete_url');\">Delete</button>";
				}
				else
				{
					$editButton = '';
					$deleteButton = '';
				}

				$class = $location->isHandicapAccessible() ? 'class="handicap_accessible"' : '';
				echo "
				<li>$editButton $deleteButton
					<a href=\"".BASE_URL."/locations/viewLocation.php?location_id={$location->getId()}\" $class>$name</a>
					$mapButton
				</li>
				";
			}
		?>
	</ul>
</div>
<?php if (defined('GOOGLE_MAP_KEY')) { ?>
<div id="location_map">
</div>
<script src="http://maps.google.com/maps?file=api&amp;v=2.x&amp;key=<?php echo GOOGLE_MAP_KEY; ?>" type="text/javascript"></script>
<script type="text/javascript">
	<?php
		$points = implode(",\n",$points);
		$info = implode(",\n",$info);

		echo "var points = [$points];\n";
		echo "var info = [$info];\n";
	?>
	var map = new GMap2(document.getElementById("location_map"));

	function loadMap()
	{
		if (GBrowserIsCompatible())
		{
			// Create map and add controls
			map.addControl(new GLargeMapControl());
			map.addControl(new GMapTypeControl());
			map.setCenter(new GLatLng(39.167119,-86.533800), 12);
			map.setMapType(G_HYBRID_MAP);

			//var boundaries = new GGeoXml("http://bloomington.in.gov/locations/Bloomington.kml");
			//map.addOverlay(boundaries);
			var bounds = new GLatLngBounds();

			for(var i=0; i<points.length; i++)
			{
				map.addOverlay(createMarker(points[i],info[i]));
				bounds.extend(points[i]);
			}
			map.setCenter(bounds.getCenter(),map.getBoundsZoomLevel(bounds));
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

	function popup(point)
	{
		if (map)
		{
			map.openInfoWindowHtml(points[point],info[point]);
			return false;
		}
		else { return true; }
	}

	setTimeout('loadMap()',500);
</script>
<?php
	} # End of If checking for GOOGLE_MAP_KEY

	} # End of If checking for $this->locationList

	if (isset($this->locationGroup))
	{
		echo '<div id="locationGroup_description">';
		echo WikiMarkup::parse($this->locationGroup->getDescription());
		echo '</div>';
	}
?>
