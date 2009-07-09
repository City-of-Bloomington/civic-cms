<?php
/**
 * @copyright 2007-2009 City of Bloomington, Indiana
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param object $this->results An array of search result hits
 * @param string $this->currentType
 *
 * Search Results are an associative array of hits.
 * Each type of result is a seperate key in the array
 */
?>
<h1>Search Results</h1>
<div class="tabBar">
	<p>Choose the type of results:</p>
	<ul>
	<?php
		# We want to display a two-level tab bar.
		# The top row will be Documents, Event, and Media
		# All the optional search results will be listed in the second row
		$url = new URL($_SERVER['SERVER_NAME'].$_SERVER['REQUEST_URI']);
		$topRow = array('Documents','Events','Media');

		$url->type = 'Documents';
		$class = ($this->currentType!='Events' && $this->currentType!='Media') ? 'class="current"' : '';
		echo "<li $class><a href=\"$url\">Documents</a></li>";

		$url->type = 'Events';
		$class = $this->currentType=='Events' ? 'class="current"' : '';
		$count = isset($this->results['Events']) ? count($this->results['Events']) : 0;
		echo "<li $class><a href=\"$url\">Events ($count)</a></li>";

		$url->type = 'Media';
		$class = $this->currentType=='Media' ? 'class="current"' : '';
		$count = isset($this->results['Media']) ? count($this->results['Media']) : 0;
		echo "<li $class><a href=\"$url\">Media ($count)</a></li>";
	?>
	</ul>
	<ul>
	<?php
		# All of the user-configured results will be here in the second row
		# Right now, these are all DocumentTypes that have been configured to be
		# displayed seperately in the search results
		$url->type = 'Documents';
		$class = ($this->currentType=='Documents') ? 'class="current"' : '';
		$count = isset($this->results['Documents']) ? count($this->results['Documents']) : 0;
		echo "<li $class><a href=\"$url\">Documents ($count)</a></li>";

		$tabs = array_keys($this->results);
		sort($tabs);
		foreach($tabs as $type)
		{
			if (!in_array($type,$topRow))
			{
				$url->type = $type;
				$class = $this->currentType == $type ? 'class="current"' : '';
				$count = isset($this->results[$type]) ? count($this->results[$type]) : 0;
				echo "<li $class><a href=\"$url\">$type ($count)</a></li>";
			}
		}
	?>
	</ul>
</div>
