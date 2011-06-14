<?php
/**
 * @copyright 2006-2009 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Section $this->section
 * @param Document $this->document The current document, which should probably be left out of the list
 */
$documentTypeList = new DocumentTypeList();
$documentTypeList->find(null,'type desc');

// We only want to display stuff if we've actually got documents
$output = '';
foreach($documentTypeList as $type) {
	$search['section_id'] = $this->section->getId();
	$search['active'] = date('Y-m-d');
	$search['featured'] = 0;
	$documents = $type->getDocuments($search);

	if (count($documents)) {
		// Each of the documentTypes must specify how they want their
		// documents displayed.  The available templates are blocks
		$block = new Block("documentTypes/listTemplates/{$type->getListTemplate()}.inc");
		$block->section = $this->section;
		$block->documentList = $documents;
		$block->documentType = $type;

		$html = $block->render();

		if ($html) {
			$output.= $html;
		}
	}
}

$name = View::escape($this->section->getName());
if ($output) {
	echo "
	<div class=\"interfaceBox\">
		<h3>Information in $name</h3>
		$output
	</div>
	";
}
