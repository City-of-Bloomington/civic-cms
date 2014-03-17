<?php
/**
 * @copyright 2014 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param DocumentType $this->documentType
 * @param FacetGroup $this->facetGroup
 */
$href = new URL($_SERVER['SERVER_NAME'].$_SERVER['REQUEST_URI']);
$href->documentType_id = $this->documentType->getId();
$href->facetGroup_id = 'none';

$class = (!isset($this->facetGroup)) ? 'class="current"' : '';
echo "
<div class=\"tabBar\">
	<h2>Organize By:</h2>
	<ul><li><a href=\"$href\" $class>Show All</a></li>
";
	$groups = new FacetGroupList();
	$groups->find();
	foreach($groups as $group) {
		if ($group->hasDocuments(['documentType_id'=>$this->documentType->getId()])) {
			$href->parameters['facetGroup_id'] = $group->getId();
			$name = View::escape($group->getName());
			$class = ($this->facetGroup && $group->getId()==$this->facetGroup->getId())
				? 'class="current"'
				: '';
			echo "<li $class><a href=\"$href\">$name</a></li>";
		}
	}
echo "</ul></div>";
