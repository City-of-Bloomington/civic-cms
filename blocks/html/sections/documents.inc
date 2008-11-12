<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Section $this->section
 * @param Document $this->document The current document, which should probably be left out of the list
 */
$documentTypeList = new DocumentTypeList();
$documentTypeList->find(null,'type desc');

# We only want to display stuff if we've actually got documents
$output = array();
foreach($documentTypeList as $type)
{
	$search['section_id'] = $this->section->getId();
	$search['active'] = date('Y-m-d');
	$search['featured'] = 0;
	$documents = $type->getDocuments($search);

	if (count($documents))
	{
		/**
		 * Each of the documentTypes must specify how they want their
		 * documents displayed.  The available templates are blocks
		 */
		$block = new Block("documentTypes/listTemplates/{$type->getListTemplate()}.inc");
		$block->section = $this->section;
		$block->documentList = $documents;
		$block->documentType = $type;

		$html = $block->render();
		if ($html) { $output[] = $html; }
	}
}

$name = View::escape($this->section->getName());
if (count($output))
{
	echo "
	<div class=\"interfaceBox\">
		<h3>Information in $name</h3>
	";
	foreach($output as $html) { echo $html; }
	echo "
	</div>
	";

}
