<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param DocumentType $this->documentType
 */
	$type = View::escape($this->documentType->getType());
	echo "<h2>$type</h2>";

	$list = new FacetList();
	$list->find();
	foreach($list as $facet)
	{
		$documents = $facet->getDocuments(array('documentType_id'=>$this->documentType->getId()));
		if (count($documents))
		{
			$name = View::escape($facet->getName());
			echo "
			<div class=\"interfaceBox\">
				<div class=\"titleBar\">$name</div>
				<ul>
			";
				foreach($documents as $document)
				{
					$title = View::escape($document->getTitle());
					echo "<li><a href=\"{$document->getURL()}\">$title</a></li>\n";
				}
			echo "
				</ul>
			</div>
			";
		}
	}
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
<button type="button" class="more" onclick="toggleSiblings(this);">More</button>
<div id="siblings" style="display:none;">
<ul><?php
		$fields = array();
		$fields['documentType_id'] = $this->documentType->getId();
		$fields['active'] = date('Y-m-d');
		$fields['facet_id'] = null;

		$list = new DocumentList($fields);
		foreach($list as $document)
		{
			$title = View::escape($document->getTitle());
			echo "<li><a href=\"{$document->getURL()}\">$title</a></li>\n";
		}
	?>
</ul>
</div>
