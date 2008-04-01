<?php
/**
 * @copyright Copyright (C) 2007-2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param DocumentList $this->documentList
 * @param Language $this->language
 */
?>
<ul>
<?php
	foreach($this->documentList as $document)
	{
		$title = View::escape($document->getTitle());
		$description = View::escape($document->getDescription());
		$url = $document->getURL();
		$url->lang = $this->language->getCode();
		echo "
		<li><a href=\"$url\">$title</a>
			<p>$description</p>
		</li>
		";
	}
?>
</ul>
