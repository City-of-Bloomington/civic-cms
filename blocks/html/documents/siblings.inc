<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Document $this->document
 */
?>
<script type="text/javascript">
	function toggleSiblings(button)
	{
		var siblings = document.getElementById('siblings');
		if (siblings.style.display === 'none')
		{
			// Display the siblings
			siblings.style.display = '';
			button.class = 'less';
			button.firstChild.nodeValue = 'Less';
		}
		else
		{
			// Hide the siblings
			siblings.style.display = 'none';
			button.class = 'more';
			button.firstChild.nodeValue = 'More';
		}
	}
</script>
<button type="button" class="more" onclick="toggleSiblings(this);">More</button>
<div id="siblings" style="display:none;">
<?php
	foreach($this->document->getSections() as $section)
	{
		$name = View::escape($section->getName());
		echo "<div class=\"interfaceBox\"><div class=\"titleBar\">$name</div><ul>";
		foreach($section->getDocuments() as $document)
		{
			if ($document->getId() != $this->document->getId())
			{
				$title = View::escape($document->getTitle());
				echo "
				<li><a href=\"".BASE_URL."/documents/viewDocument.php?document_id={$document->getId()}\">
					$title</a>
				</li>
				";
			}
		}
		echo "</ul></div>";
	}
?>
</div>
