<?php
/**
 * @copyright 2007-2009 City of Bloomington, Indiana.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Facet $this->facet
 */
if (count($this->facet->getDocuments())) {
	echo '<ul>';
	foreach ($this->facet->getDocuments() as $document) {
		$title = View::escape($document->getTitle());
		echo "<li><a href=\"{$document->getURL()}\">$title</a></li>";
	}
	echo '</ul>';
}