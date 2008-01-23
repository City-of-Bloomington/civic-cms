<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Section $this->section
 * @param Document $this->document The current document, which should probably be left out of the list
 */
$documentTypeList = new DocumentTypeList();
$documentTypeList->find();

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
		$documentListHTML = '';
		foreach($documents as $document)
		{
			if ($document->getId() != $this->section->getDocument()->getId())
			{
				$info = array();
				foreach($type->getDocumentInfoFields() as $field)
				{
					$get = 'get'.ucfirst($field);
					switch ($field)
					{
						case 'created':
						case 'modified':
						case 'publishDate':
						case 'retireDate':
							$info[] = $document->$get('Y-m-d');
						break;

						case 'createdBy':
						case 'modifiedBy':
							$info[] = $document->$get()->getUsername();
						break;

						case 'DocumentType':
						case 'Department':
							$info[] = View::escape($document->$get()->getName());
						break;

						default:
							$info[] = View::escape($document->$get());
					}
				}
				$info = implode(' - ',$info);

				$documentListHTML.= "
					<li class=\"closed\">
						<a href=\"{$document->getURL()}\">$info</a>
					</li>
				";
			}
		}

		if ($documentListHTML)
		{
			$name = View::escape(Inflector::pluralize($type->getType()));
			$output[] = "
			<li class=\"closed\">
				<a href=\"".BASE_URL."/documentTypes/documents.php?documentType_id={$type->getId()}\">$name</a>
				<ul>
					$documentListHTML
				</ul>
			</li>
			";
		}
	}
}

$name = View::escape($this->section->getName());
if (count($output))
{
	echo "
	<div class=\"interfaceBox\">
		<h3>Information in $name</h3>
		<ul class=\"expandable\">
	";
	foreach($output as $html) { echo $html; }
	echo "
		</ul>
	</div>
	";

	/**
	 * This fires off the JavaScript that turns the expandable UL into a tree
	 * This library has a bug - it will freeze if the <li> elements are not on their
	 * own line.  Make sure to put line breaks for each <li>
	 */
	include_once APPLICATION_HOME.'/includes/js/tree.inc';
}
