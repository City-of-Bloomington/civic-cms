<?php
/**
 * @copyright Copyright (C) 2006-2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Document $this->document
 */
?>
<script type="text/javascript">
	function toggleDisplay(element,button)
	{
		var siblings = document.getElementById(element);
		if (siblings.style.display === 'none')
		{
			// Display the siblings
			siblings.style.display = '';
			button.className = 'less';
			button.firstChild.nodeValue = 'Less';
		}
		else
		{
			// Hide the siblings
			siblings.style.display = 'none';
			button.className = 'more';
			button.firstChild.nodeValue = 'More';
		}
	}
</script>
<?php
	$sort = $this->document->getDocumentType()->getOrdering();
	foreach($this->document->getSections() as $section)
	{
		$documents = $section->getDocuments($sort);
		# The curent document will always be included in this list,
		# But we only want to show this box if there are other documents
		# in this list
		if (count($documents)>1)
		{
			$name = View::escape($section->getName());
			echo "
			<div class=\"interfaceBox siblings\">
				<h3>Information in $name</h3>
				<ul>
			";
			# List the first five documents
			$count = 0;
			foreach($documents as $document)
			{
				if ($document->getId() != $this->document->getId())
				{
					# When we've displayed five documents, start new list, but keep it hidden
					if ($count==5)
					{
						echo "
						</ul>
						<button type=\"button\" class=\"more\" onclick=\"toggleDisplay('siblings_{$section->getId()}',this);\">More</button>
						<ul id=\"siblings_{$section->getId()}\" style=\"display:none;\">";
					}

					$count++; # Count how many documents we've displayed
					$title = View::escape($document->getTitle());
					echo "<li><a href=\"{$document->getURL()}\">$title</a></li>\n";
				}
			}
			echo "
				</ul>
			</div>
			";
		}
	}
?>
