<?php
/**
 * @copyright 2010 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param DocumentType $this->documentType
 * @param FacetGroup $this->facetGroup
 */
$documents = new DocumentList();
$documents->find(array('documentType_id'=>$this->documentType->getId(),
				'active'=>date('Y-m-d')),
				'publishDate desc',
				isset($_GET['limit']) ? (int) $_GET['limit'] : null);
echo "<documents>";
foreach ($documents as $document) {
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
