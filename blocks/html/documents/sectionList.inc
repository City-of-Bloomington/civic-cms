<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Document $this->document
 */
?>
<h1><?php echo View::escape($this->document->getTitle()); ?></h1>
<h2>Current Sections</h2>
<?php
	if (count($this->document->getSections()))
	{
		echo '<ul>';
		foreach($this->document->getSectionDocuments() as $sectionDocument)
		{
			$section = $sectionDocument->getSection();
			$name = View::escape($section->getName());

			echo "
			<li><a href=\"{$section->getURL()}\">$name</a></li>
			";
		}
		echo '</ul';

	}
?>
