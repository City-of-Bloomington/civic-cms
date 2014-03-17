<?php
/**
 * @copyright 2010-2014 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param DocumentType $this->documentType
 * @param DocumentList $this->documents
 */
foreach ($this->documents as $document) {
	$output[] = [
		'title'      => $document->getTitle(),
		'url'        => "{$document->getURL()}",
		'publishDate'=> $document->getPublishDate()
	];
}
echo json_encode($output);
