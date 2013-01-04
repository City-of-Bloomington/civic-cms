<?php
/**
 * @copyright 2012-2013 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param LocationList $this->locationList
 * @param string $this->title
 * @param LocationGroup $this->locationGroup
 */
?>
<div class="interfaceBox" id="location_list">
	<h2>
		<?php
			$return_url = new URL("$_SERVER[SERVER_NAME]$_SERVER[REQUEST_URI]");

			if (userHasRole(array('Administrator','Webmaster','Content Creator')))
			{
				$add_url = new URL(BASE_URL.'/locations/updateLocation.php');
				$add_url->return_url = $return_url;
				echo "<a class=\"addSmall button\" href=\"$add_url\">Add</a>";
			}

			$url = new URL(BASE_URL.'/locations');
			$url->format = 'kml';
			$url->locationGroup_id = isset($this->locationGroup) ? $this->locationGroup->getId() : 0;
			$title = View::escape($this->title);
			echo "<a class=\"kmlFeed button\" href=\"$url\">$title KML</a>";

			echo View::escape($this->title);
		?>
	</h2>
	<ul><?php
			$points = array();
			foreach ($this->locationList as $location) {
				$name = View::escape($location->getName());
				$description = WikiMarkup::parse($location->getDescription());

				# Check if the installation has a Google Maps Key
				# Make sure the location has Latitude and Longitude before trying to map it
				if (defined('GOOGLE_MAPS')
					&& ($location->getLatitude() && $location->getLongitude())) {

					$n = addslashes($name);
					$d = addslashes(str_replace(array("\r\n","\n","\r"),' ',$description));
					$a = addslashes($location->getAddress());

					$title = "<h3><a href=\"{$location->getURL()}\">$n</a></h3>";
					$desc = "<p>$d</p>";
					$directionsURL = "http://maps.google.com/?q=to:$n@{$location->getLatitude()},{$location->getLongitude()}";
					$directions = "<p>Get Directions: <a href=\"$directionsURL\" onclick=\"window.open(\'$directionsURL\');return false;\">To Here</a></p>";
					$address = "<address>$a</address>";

					$points[] = array(
						'latitude' => $location->getLatitude(),
						'longitude'=> $location->getLongitude(),
						'info' => "{$title}{$desc}{$a}{$directions}"
					);

					$i = count($points) - 1;
					$mapButton = "<a href=\"#map\" onclick=\"LOCATION_MAP.popup($i)\" class=\"reveal button\">Reveal In Map</a>";
				}
				else { $mapButton = ''; }


				if (isset($_SESSION['USER'])
					&& $location->permitsEditingBy($_SESSION['USER'])) {
					$edit_url = new URL(BASE_URL.'/locations/updateLocation.php');
					$edit_url->location_id = $location->getId();
					$edit_url->return_url = $return_url;
					$editButton = "<a class=\"editSmall button\" href=\"$edit_url\">Edit</a>";

					$delete_url = new URL(BASE_URL.'/locations/deleteLocation.php');
					$delete_url->location_id = $location->getId();
					$delete_url->return_url = $return_url;
					$deleteButton = "<button type=\"button\" class=\"deleteSmall\" onclick=\"FRAMEWORK.deleteConfirmation('$delete_url');\">Delete</button>";
				}
				else {
					$editButton   = '';
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
<?php
	if (defined('GOOGLE_MAPS')) {
		$points = json_encode($points);

		$this->template->addToAsset('scripts', GOOGLE_MAPS);
		$this->template->addToAsset('scripts', BASE_URL.'/js/map.js');

		echo "
		<div id=\"location_map\"></div>
		<script type=\"text/javascript\">
			var points = $points;
		</script>
		";
	}

	if (isset($this->locationGroup)) {
		echo '<div id="locationGroup_description">';
		echo WikiMarkup::parse($this->locationGroup->getDescription());
		echo '</div>';
	}
?>
