<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Document $this->document
 * @param FacetGroupList $this->facetGroupList
 * @param URL $this->return_url
 * @param int $this->instance_id
 */
?>
<form id="documentForm" method="post" action="<?php echo $_SERVER['PHP_SELF']; ?>">
	<?php
		foreach($this->facetGroupList as $group)
		{
			$name = View::escape($group->getName());
			echo "<fieldset><legend>$name</legend>";

			foreach($group->getFacets() as $facet)
			{
				$facetName = View::escape($facet->getName());
				if ($this->document->hasFacet($facet)) { $checked = "checked=\"checked\""; } else { $checked = ""; }
				echo "<label><input type=\"checkbox\" name=\"document[facets][{$facet->getId()}]\" value=\"{$facet->getId()}\" $checked />$facetName</label>";
			}
			echo "</fieldset>";
		}
	?>
	<div>
		<input type="hidden" name="tab" id="tab" value="info" />
		<input type="hidden" name="action" id="action" value="next" />
		<input type="hidden" name="return_url" value="<?php echo $this->return_url; ?>" />
		<input type="hidden" name="instance_id" value="<?php echo $this->instance_id; ?>" />
	</div>
</form>
