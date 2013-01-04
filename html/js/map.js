"use strict";
/**
 * Renders a Google Map into the designated DIV
 *
 * This script can currently only render one map on the screen at a time.
 * The DIV should have an ID of "location_map"
 * The HTML should create a global JavaScript variable for all the points.
 *
 * <script type="text/javascript">
 * var points = [
 *		{latitude:39.123192, longitude:-86.532166, info:"<p>HTML for the marker bubble</p>"},
 * 		{latitude:39.153831, longitude:-86.536102, info:"<p>HTML for the marker bubble</p>"}
 * ]
 * </script>
 *
 * @copyright 2013 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param array points
 * @param array info
 */
var LOCATION_MAP = {
	map: new google.maps.Map(document.getElementById('location_map'), {
		zoom: 15,
		center: new google.maps.LatLng(points[0].latitude, points[0].longitude),
		mapTypeId: google.maps.MapTypeId.ROADMAP
	}),
	markers: [],
	infoWindow: new google.maps.InfoWindow(),
	markerBounds: new google.maps.LatLngBounds(),
	initialize: function() {
		var len = points.length;
		for (var i=0; i<len; i++) {
			// Create the marker
			LOCATION_MAP.markers.push(new google.maps.Marker({
				position: new google.maps.LatLng(points[i].latitude, points[i].longitude),
				map: LOCATION_MAP.map
			}));
			LOCATION_MAP.markerBounds.extend(LOCATION_MAP.markers[i].position);

			google.maps.event.addListener(LOCATION_MAP.markers[i], 'click', function(i) {
				return function() {
					LOCATION_MAP.popup(i);
				}
			}(i));
		}
		if (points.length > 1) {
			LOCATION_MAP.map.fitBounds(LOCATION_MAP.markerBounds);
		}
	},
	popup: function(i) {
		LOCATION_MAP.infoWindow.setContent(points[i].info);
		LOCATION_MAP.infoWindow.open(LOCATION_MAP.map, LOCATION_MAP.markers[i]);
	}
};
google.maps.event.addDomListener(window, 'load', LOCATION_MAP.initialize);
