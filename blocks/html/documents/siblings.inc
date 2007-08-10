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
			button.className = 'less';
			button.firstChild.nodeValue = 'Less Documents';
		}
		else
		{
			// Hide the siblings
			siblings.style.display = 'none';
			button.className = 'more';
			button.firstChild.nodeValue = 'More Documents';
		}
	}
</script>
<div><button type="button" class="more" onclick="toggleSiblings(this);">More Documents</button></div>
<div id="siblings" style="display:none;">
<?php
	foreach($this->document->getSections() as $section)
	{
		$name = View::escape($section->getName());
		echo "
		<div class=\"interfaceBox\">
			<div class=\"titleBar\">$name Documents</div>
			<ul>
		";
		foreach($section->getDocuments() as $document)
		{
			if ($document->getId() != $this->document->getId())
			{
				$title = View::escape($document->getTitle());
				echo "<li><a href=\"{$document->getURL()}\">$title</a></li>\n";
			}
		}
		echo "
			</ul>
		</div>
		";
	}
?>
</div>
