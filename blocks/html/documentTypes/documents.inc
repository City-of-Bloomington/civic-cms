<?php
/**
 * @copyright 2007-2014 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param DocumentType $this->documentType
 * @param DocumentList $this->documents
 */
if (count($this->documents)) {
	echo '<ul>';
	foreach($this->documents as $document) {
		$info = View::escape(implode(' - ',$document->getInfo()));
		$class = preg_match('/Please add a/',$info) ? 'class="badlink"' : '';
		echo "<li><a href=\"{$document->getURL()}\" $class>$info</a></li>";
	}
	echo '</ul>';
}
