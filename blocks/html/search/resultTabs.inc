<?php
/**
 * @copyright 2007-2014 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Apache_Solr_Response $this->solrObject
 */
$currentRecordType = !empty($_GET['recordType']) ? $_GET['recordType'] : 'document';
$currentType       = !empty($_GET['type'])       ? $_GET['type']       : 'Documents';

$facets = &$this->solrObject->facet_counts->facet_fields;
?>
<h1>Search Results</h1>
<div class="tabBar">
	<p>Choose the type of results:</p>
	<ul>
	<?php
		# We want to display a two-level tab bar.
		# The top row will be recordType: Documents, Event, and Media
		# The second row will be type: (Documents, News, Agenda)
		# All the optional search results will be listed in the second row
		$url = new URL($_SERVER['SERVER_NAME'].$_SERVER['REQUEST_URI']);

		$url->recordType = 'document';
		$class = ($currentRecordType!='event' && $currentRecordType!='media') ? 'class="current"' : '';
		$count = $facets->recordType->document;
		echo "<li $class><a href=\"$url\">Documents ($count)</a></li>";

		$url->recordType = 'event';
		$class = $currentRecordType=='event' ? 'class="current"' : '';
		$count = $facets->recordType->event;
		echo "<li $class><a href=\"$url\">Events ($count)</a></li>";

		$url->recordType = 'media';
		$class = $currentRecordType=='media' ? 'class="current"' : '';
		$count = $facets->recordType->media;
		echo "<li $class><a href=\"$url\">Media ($count)</a></li>";
	?>
	</ul>
	<ul>
	<?php
		# All of the user-configured results will be here in the second row
		# Right now, these are all DocumentTypes that have been configured to be
		# displayed seperately in the search results
		if ($currentRecordType == 'document') {
			$url->recordType = 'document';

			// Pull "Documents" out first. All the other tabs can be ordered any which way
			$type = 'Documents';
			$count = $facets->type->Documents;
			$url->type = $type;
			$class = $type==$currentType ? 'class="current"' : '';
			echo "<li $class><a href=\"$url\">$type ($count)</a></li>";

			foreach ($facets->type as $type=>$count) {
				// We've already rendered the Documents tab
				if ($type != 'Documents') {
					$url->type = $type;
					$class = $type==$currentType ? 'class="current"' : '';
					echo "<li $class><a href=\"$url\">$type ($count)</a></li>";
				}
			}
		}
	?>
	</ul>
</div>
