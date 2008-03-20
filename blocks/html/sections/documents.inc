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
		$documentListHTML = '';
		foreach($documents as $document)
		{
			if ($document->getId() != $this->section->getDocument()->getId())
			{
				$info = implode(' - ',$document->getInfo());
				$class = preg_match('/Please add a/',$info) ? 'class="badlink"' : '';

				$documentListHTML.= "
					<li>
						<a href=\"{$document->getURL()}\" $class>$info</a>
					</li>
				";
			}
		}

		if ($documentListHTML)
		{
			$name = View::escape(Inflector::pluralize($type->getType()));
			$output[] = "
			<li class=\"liOpen\">
				$name
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
		<ul class=\"mktree\">
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
