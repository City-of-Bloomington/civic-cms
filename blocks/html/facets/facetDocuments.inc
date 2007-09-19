<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Tag $this->tag
 */
	$name = View::escape($this->tag->getName());
	$description = WikiMarkup::parse($this->tag->getDescription());
	echo "
	<h2>$name</h2>
	<div>$description</div>
	";

	$displayedDocuments = array();
	foreach($this->tag->getRelatedGroups() as $group)
	{
		foreach($group->getTags() as $tag)
		{
			if ($tag->getId() != $this->tag->getId())
			{
				$list = new DocumentList(array('tag_id'=>array($this->tag->getId(),$tag->getId()),'active'=>date('Y-m-d')));
				if (count($list))
				{
					$name = View::escape($tag->getName());
					echo "
					<div class=\"interfaceBox\">
						<div class=\"titleBar\">$name</div>
						<ul>
					";
						foreach($list as $document)
						{
							$displayedDocuments[$document->getId()] = $document;

							$title = View::escape($document->getTitle());
							echo "<li><a href=\"{$document->getURL()}\">$title</a></li>\n";
						}
					echo "
						</ul>
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
	$documents = $this->tag->getDocuments();
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
