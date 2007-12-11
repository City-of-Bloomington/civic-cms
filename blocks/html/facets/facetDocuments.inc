<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Facet $this->facet
 */
	$name = View::escape($this->facet->getName());
	$description = WikiMarkup::parse($this->facet->getDescription());
	echo "
	<h1>$name</h1>
	<div>$description</div>
	";

	$displayedDocuments = array();
	foreach($this->facet->getRelatedGroups() as $group)
	{
		foreach($group->getFacets() as $facet)
		{
			if ($facet->getId() != $this->facet->getId())
			{
				$list = new DocumentList(array('facet_id'=>array($this->facet->getId(),$facet->getId()),'active'=>date('Y-m-d')));
				if (count($list))
				{
					$name = View::escape($facet->getName());
					echo "
					<div class=\"interfaceBox\">
						<div class=\"titleBar\">$name</div>
						<ul>
					";
						foreach($list as $document)
						{
							$displayedDocuments[$document->getId()] = $document;

							$title = $document->getFeature_title() ? $document->getFeature_title() : $document->getTitle();
							$title = View::escape($title);
							echo "<li><a href=\"{$document->getURL()}\">$title</a></li>\n";
						}
					echo "
						</ul>
						<a href=\"#top\">[Top]</a>
					</div>
					";
				}
			}
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
<?php
	$documents = $this->facet->getDocuments();
	# Don't bother showing anything if all these documents have already been listed above
	if (count($documents)>count($displayedDocuments))
	{
		if (count($displayedDocuments))
		{
			echo "
			<button type=\"button\" class=\"more\" onclick=\"toggleSiblings(this);\">More</button>
			<div id=\"siblings\" style=\"display:none;\">
			";
		}
		else { echo '<div id="siblings">'; }

		echo '<ul>';
		foreach($documents as $document)
		{
			if (!in_array($document->getId(),array_keys($displayedDocuments)))
			{
				$title = View::escape($document->getTitle());
				echo "<li><a href=\"{$document->getURL()}\">$title</a></li>";
			}
		}
		echo '</ul></div>';
	}
?>
