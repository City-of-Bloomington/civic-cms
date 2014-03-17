<?php
/**
 * @copyright 2010-2014 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param DocumentType $this->documentType
 * @param DocumentList $this->documents
 */
echo "<documents>";
foreach ($this->documents as $document) {
	$title = View::escape($document->getTitle());
	echo "
	<document id=\"{$document->getId()}\">
		<url>{$document->getURL()}</url>
		<title>$title</title>
		<publishDate>{$document->getPublishDate('Y-m-d')}</publishDate>
	</document>
	";
}
echo "</documents>";
