<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Section $this->section
 * @param Document $this->document The current document, which should probably be left out of the list
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
	$sort = isset($this->document) ? $this->document->getDocumentType()->getOrdering() : null;
	$documents = $this->section->getDocuments($sort);
	# The curent document will always be included in this list,
	# But we only want to show this box if there are other documents
	# in this list
	if (count($documents)>1)
	{
		$name = View::escape($this->section->getName());
		echo "
		<div class=\"interfaceBox siblings\">
			<h3>Information in $name</h3>
			<ul>
		";
				#<a href=\"".BASE_URL."/sections/viewSection.php?section_id={$this->section->getId()};format=rss\" class=\"rss\">
				#	<img src=\"".BASE_URL."/skins/default/images/feed-icon-14x14.png\" alt=\"RSS\" />
				#</a>

		# Don't list Featured Documents.  They should have already been displayed
		$list = new DocumentList(array('section_id'=>$this->section->getId(),'featured'=>1,'active'=>date('Y-m-d')));
		$featured = array();
		foreach($list as $d) { $featured[] = $d->getId(); }

		# List the first five documents
		$count = 0;
		foreach($documents as $document)
		{
			# Check to see if we should display this document
			if ($document->getId()!=$this->document->getId() && # The current document should be left out of this list
				!in_array($document->getId(),$featured) # Featured documents should have already been displayed
				)
			{
				# When we've displayed five documents, start new list, but keep it hidden
				if ($count==5)
				{
					echo "
					</ul>
					<button type=\"button\" class=\"more\" onclick=\"toggleDisplay('siblings_{$this->section->getId()}',this);\">More</button>
					<ul id=\"siblings_{$this->section->getId()}\" style=\"display:none;\">";
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
?>
