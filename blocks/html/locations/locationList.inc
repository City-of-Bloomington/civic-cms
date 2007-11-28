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
<h1>Locations</h1>
<form method="get" action="<?php echo $_SERVER['PHP_SELF']; ?>">
<fieldset>
	<select name="locationGroup_id" onchange="this.form.submit();">
		<option value="">Choose a group</option>
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
			if (userHasRole(array('Administrator','Webmaster','Content Creator')))
			{
				echo "<button type=\"button\" class=\"addSmall\" onclick=\"document.location.href='".BASE_URL."/locations/updateLocation.php';\">Add</button>";
			}
			echo View::escape($this->title);
		?>
	</div>
	<ul><?php
			$points = array();
			$info = array();
			$return_url = "http://$_SERVER[SERVER_NAME]$_SERVER[REQUEST_URI]";
			foreach($this->locationList as $location)
			{
				$name = View::escape($location->getName());
				$description = View::escape($location->getDescription());

				# Make sure the location has Latitude and Longitude before trying to map it
				if ($location->getLatitude() && $location->getLongitude())
				{
					$points[] = "new GLatLng({$location->getLatitude()},{$location->getLongitude()})";
					$info[] = '"<h3>'.addslashes($name).'</h3><p>'.addslashes($description).'</p>"';

					$i = count($points) - 1;
					$mapButton = "<button type=\"button\" onclick=\"popup($i);\">Map It</button>";
				}
				else { $mapButton = ''; }


				if (isset($_SESSION['USER']) && $location->permitsEditingBy($_SESSION['USER']))
				{
					$edit_url = new URL(BASE_URL.'/locations/updateLocation.php');
					$edit_url->location_id = $location->getId();
					$edit_url->return_url = $return_url;
					$editButton = "<button type=\"button\" class=\"editSmall\" onclick=\"document.location.href='$edit_url';\">Edit</button>";
				}
				else { $editButton = ''; }

				echo "
				<li>$editButton
					<a href=\"".BASE_URL."/locations/viewLocation.php?location_id={$location->getId()}\">$name</a>
					$mapButton
				</li>
				";
			}
		?>
	</ul>
</div>

<div id="location_map">
</div>
<script src="http://maps.google.com/maps?file=api&amp;v=2.77&amp;key=ABQIAAAACqoQOZ2EAqg13jBR94AfexQNf7mhA6pY0zZO8gsdk0EdOTN8sxQDa2L0KB-dgEIEE-5Qas2VnQE6DQ" type="text/javascript"></script>
<script type="text/javascript">
	<?php
		$points = implode(',',$points);
		$info = implode(',',$info);

		echo "var points = [$points];\n";
		echo "var info = [$info];\n";
	?>
	var map = new GMap2(document.getElementById("location_map"));
	function loadMap()
	{
		if (GBrowserIsCompatible())
		{
			// Create map and add controls
			map.addControl(new GSmallMapControl());
			map.addControl(new GMapTypeControl());
			map.setCenter(new GLatLng(39.167119,-86.533800), 12);

			for(var i=0; i<points.length; i++) { map.addOverlay(createMarker(points[i],info[i])); }
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
	} # End of If checking for $this->locationList

	if (isset($this->locationGroup))
	{
		echo '<div id="locationGroup_description">';
		echo WikiMarkup::parse($this->locationGroup->getDescription());
		echo '</div>';
	}
?>
