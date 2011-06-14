<?php
/**
 * @copyright 2007-2009 City of Bloomington, Indiana.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Facet $this->facet
 */
$items = $this->facet->getItems();
if (count($items)) {
	echo '<ul>';
	foreach ($items as $item) {
		$title = $item instanceof Document ? $item->getTitle() : $item->getName();
		$title = View::escape($title);
		echo "<li><a href=\"{$item->getURL()}\">$title</a></li>";
	}
	echo '</ul>';
}