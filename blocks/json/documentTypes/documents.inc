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
				'active'=>date('d-m-Y')),
				'publishDate desc',
				isset($_GET['limit']) ? (int) $_GET['limit'] : null);
$output = array();
foreach ($documents as $document) {
	$output[] = array('title'=>$document->getTitle(),
						'url'=>"{$document->getURL()}",
						'publishDate'=>$document->getPublishDate());
}
echo json_encode($output);