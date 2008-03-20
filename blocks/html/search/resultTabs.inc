<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param object $this->results
 * @param string $this->currentType
 */
?>
<h1>Search Results</h1>
<div class="tabBar">
	<p>Choose the type of results:</p>
	<ul>
	<?php
		$url = new URL($_SERVER['SERVER_NAME'].$_SERVER['REQUEST_URI']);

		$url->type = 'Document';
		$class = $this->currentType=='Documents' ? 'class="current"' : '';
		$count = isset($this->results['documents']) ? count($this->results['documents']) : 0;
		echo "<li $class><a href=\"$url\">Documents</a> ($count)</li>";

		$url->type = 'Event';
		$class = $this->currentType=='Events' ? 'class="current"' : '';
		$count = isset($this->results['events']) ? count($this->results['events']) : 0;
		echo "<li $class><a href=\"$url\">Events</a> ($count)</li>";

		$url->type = 'Media';
		$class = $this->currentType=='Media' ? 'class="current"' : '';
		$count = isset($this->results['media']) ? count($this->results['media']) : 0;
		echo "<li $class><a href=\"$url\">Files &amp; Media</a> ($count)</li>";
	?>
	</ul>
</div>
