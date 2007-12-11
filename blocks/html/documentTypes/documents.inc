<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param DocumentType $this->documentType
 * @param FacetGroup $this->facetGroup
 */
	$type = View::escape($this->documentType->getType());
	$href = new URL("http://$_SERVER[SERVER_NAME]$_SERVER[PHP_SELF]");
	$href->parameters['documentType_id'] = $this->documentType->getId();
	$href->parameters['facetGroup_id'] = 'none';

	$class = (!isset($this->facetGroup)) ? 'class="current"' : '';
	echo "
	<h1><a href=\"$href\">$type</a>
		<a href=\"$href;format=rss\" class=\"rss\">
			<img src=\"".BASE_URL."/skins/default/images/feed-icon-14x14.png\" alt=\"RSS $type feed\" />
		</a>
	</h1>
	<div class=\"tabBar\">
	<ul><li><a href=\"$href\" $class>Show All</a></li>
		<li>Organize By:</li>
	";

	$groups = new FacetGroupList();
	$groups->find();
	foreach($groups as $group)
	{
		if ($group->hasDocuments(array('documentType_id'=>$this->documentType->getId())))
		{
			$href->parameters['facetGroup_id'] = $group->getId();
			$name = View::escape($group->getName());
			$class = (isset($this->facetGroup) && $group->getId()==$this->facetGroup->getId()) ? 'class="current"' : '';
			echo "<li><a href=\"$href\" $class>$name</a></li>";
		}
	}

	echo "
	</ul>
	</div>
	";





	# List all the documents, grouped by Facet - inside the current FacetGroup
	if (isset($this->facetGroup))
	{
		foreach($this->facetGroup->getFacets() as $facet)
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
	# Otherwise, just list all the documents
	else
	{
		$documents = $this->documentType->getDocuments();
		if (count($documents))
		{
			echo '<ul>';
			foreach($documents as $document)
			{
				$title = $document->getFeature_title() ? $document->getFeature_title() : $document->getTitle();
				$title = View::escape($title);
				echo "<li><a href=\"{$document->getURL()}\">$title</a></li>\n";
			}
			echo '</ul>';
		}
	}
?>
