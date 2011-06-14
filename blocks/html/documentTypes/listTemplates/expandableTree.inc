<?php
/**
 * This is a template used for listing documents.
 *
 * It will list the documents as an unordered list, which can be
 * expanded and collapsed using Javascript
 *
 * @copyright 2008-2009 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Section $this->section
 * @param DocumentList $this->documentList
 * @param DocumentType $this->documentType
 */
if (count($this->documentList)) {
	$documentListHTML = '';
	foreach ($this->documentList as $document) {
		if ($document->getId() != $this->section->getDocument()->getId()) {
			$info = implode(' - ',$document->getInfo());
			$class = preg_match('/Please add a/',$info) ? 'class="badlink"' : '';

			$documentListHTML.= "
				<li><a href=\"{$document->getURL()}\" $class>$info</a></li>
			";
		}
	}

	if ($documentListHTML) {
		$name = View::escape(Inflector::pluralize($this->documentType->getType()));
		echo "
		<ul class=\"mktree\">
			<li class=\"liOpen\">
				$name
				<ul>$documentListHTML</ul>
			</li>
		</ul>
		";
		/**
		 * This fires off the JavaScript that turns the expandable UL into a tree
		 * This library has a bug - it will freeze if the <li> elements are not on their
		 * own line.  Make sure to put line breaks for each <li>
		 */
		include_once APPLICATION_HOME.'/includes/js/tree.inc';
	}
}
