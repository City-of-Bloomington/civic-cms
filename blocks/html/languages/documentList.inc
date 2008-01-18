<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param DocumentList $this->documentList
 * @param Language $this->language
 */
?>
<h1><?php echo $this->language->getNative(); ?></h1>
<ul>
<?php
	foreach($this->documentList as $document)
	{
		$title = View::escape($document->getTitle());
		$description = View::escape($document->getDescription());
		echo "
		<li><a href=\"{$document->getURL()}\">$title</a>
			<p>$description</p>
		</li>
		";
	}
?>
</ul>
