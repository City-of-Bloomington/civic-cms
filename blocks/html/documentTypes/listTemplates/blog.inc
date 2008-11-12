<?php
/**
 * @copyright Copyright (C) 2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Section $this->section
 * @param DocumentList $this->documentList
 * @param DocumentType $this->documentType
 *
 * This is a template used for listing documents.  It will list
 * the documents in a blog style.  Each document will display it's content
 * inside a div with a Header displaying date and title
 */
if (count($this->documentList))
{
	$documentListHTML = '';
	foreach($this->documentList as $document)
	{
		if ($document->getId() != $this->section->getDocument()->getId())
		{
			$info = implode(' - ',$document->getInfo());
			$class = preg_match('/Please add a/',$info) ? 'class="badlink"' : '';

			$content = new Block('documents/viewDocument.inc');
			$content->document = $document;
			$content->section = $this->section;

			echo "
			<div class=\"blogPost\">
				<h2>
					<a href=\"{$document->getURL()}\" $class>$info</a>
				</h2>
				{$content->render()}
			</div>
			";
		}
	}
}
