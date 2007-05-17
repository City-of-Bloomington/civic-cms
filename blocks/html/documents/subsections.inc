<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Document $this->document
 */
?>
<script type="text/javascript">
	function toggleSubsections(button)
	{
		var subsections = document.getElementById('subsections');
		if (subsections.style.display === 'none')
		{
			// Display the subsections
			subsections.style.display = '';
			button.class = 'less';
			button.firstChild.nodeValue = 'Less';
		}
		else
		{
			// Hide the subsections
			subsections.style.display = 'none';
			button.class = 'more';
			button.firstChild.nodeValue = 'More';
		}
	}
</script>
<button type="button" class="more" onclick="toggleSubsections(this);">More</button>
<div id="subsections" style="display:none;">
<?php
	foreach($this->document->getSections() as $section)
	{
		echo "<div class=\"interfaceBox\"><div class=\"titleBar\">$section</div><ul>";
		foreach($section->getDocuments() as $document)
		{
			if ($document->getId() != $this->document->getId())
			{
				echo "
				<li><a href=\"".BASE_URL."/documents/viewDocument.php?document_id={$document->getId()}\">
					{$this->escape($document->getTitle())}</a>
				</li>
				";
			}
		}
		foreach($section->getChildren() as $child)
		{
			echo "
			<li><a href=\"".BASE_URL."/documents/viewDocument.php?document_id={$child->getDocument_id()}\">
				{$this->escape($child->getName())}
				<ul>
			";
				foreach($child->getDocuments() as $document)
				{
					if ($document->getId() != $child->getDocument_id())
					{
						echo "
						<li><a href=\"".BASE_URL."/documents/viewDocument.php?document_id={$document->getId()}\">
							{$this->escape($document->getTitle())}</a>
						</li>
						";
					}
				}
			echo "
				</ul>
				</a>
			</li>
			";
		}
		echo "</ul></div>";
	}
?>
</div>
