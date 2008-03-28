<?php
/**
 * @copyright Copyright (C) 2007-2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param DocumentType $this->documentType
 * @param FacetGroup $this->facetGroup
 */
$href = new URL($_SERVER['SERVER_NAME'].$_SERVER['PHP_SELF']);
$href->documentType_id = $this->documentType->getId();
$href->facetGroup_id = 'none';

$class = (!isset($this->facetGroup)) ? 'class="current"' : '';
echo "
<div class=\"tabBar\">
<h1>Organize By:</h1>
<ul><li><a href=\"$href\" $class>Show All</a></li>
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
		echo "<li $class><a href=\"$href\">$name</a></li>";
	}
}
echo "</ul></div>";





# List all the documents, grouped by Facet - inside the current FacetGroup
if (isset($this->facetGroup))
{
	echo "
	<div class=\"table-of-contents\">
		<form method=\"get\">
		<fieldset>
			<label for=\"table-of-contents-anchor\">Table of Contents:</label>
			<select name=\"anchor\" id=\"table-of-contents-anchor\" onchange=\"document.location.href='#'+this.options[this.selectedIndex].value;\">
	";
			foreach($this->facetGroup->getFacets() as $facet)
			{
				$name = View::escape($facet->getName());
				$anchor = WikiMarkup::wikify($facet->getName());
				echo "<option value=\"$anchor\">$name</option>\n";
			}
	echo "
			</select>
		</fieldset>
		</form>
	</div>
	";

	foreach($this->facetGroup->getFacets() as $facet)
	{
		$documents = new DocumentList();
		$fields = array('facet_id'=>$facet->getId(),
						'active'=>date('Y-m-d'),
						'documentType_id'=>$this->documentType->getId());
		$sort = $this->documentType->getOrdering();
		$documents->find($fields,$sort);

		if (count($documents))
		{
			$name = View::escape($facet->getName());
			$anchor = WikiMarkup::wikify($facet->getName());
			echo "
			<div class=\"interfaceBox\">
				<h2><a id=\"$anchor\">$name</a></h2>
				<ul>
			";
				foreach($documents as $document)
				{
					$info = View::escape(implode(' - ',$document->getInfo()));
					$class = preg_match('/Please add a/',$info) ? 'class="badlink"' : '';
					echo "<li><a href=\"{$document->getURL()}\" $class>$info</a></li>\n";
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
			$info = View::escape(implode(' - ',$document->getInfo()));
			$class = preg_match('/Please add a/',$info) ? 'class="badlink"' : '';
			echo "<li><a href=\"{$document->getURL()}\" $class>$info</a></li>\n";
		}
		echo '</ul>';
	}
}
