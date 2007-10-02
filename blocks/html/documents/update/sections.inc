<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Document $this->document
 * @param SectionList $this->sectionList
 * @param URL $this->return_url
 * @param int $this->instance_id
 */
?>
<form id="documentForm" method="post" action="<?php echo $_SERVER['PHP_SELF']; ?>">
	<fieldset><legend class="required">Sections</legend>
		<input type="hidden" name="tab" id="tab" value="facets" />
		<input type="hidden" name="action" id="action" value="next" />
		<input type="hidden" name="return_url" value="<?php echo $this->return_url; ?>" />
		<input type="hidden" name="instance_id" value="<?php echo $this->instance_id; ?>" />
		<input type="hidden" name="continue" id="continue" value="true" />
	<table>
	<tr><th>Section</th><th>Linked</th><th>Featured</th></tr>
		<?php
			$document_sections = $this->document->getDocumentSections();

			foreach ($this->sectionList as $section)
			{
				$linked = $this->document->hasSection($section) ? 'checked="checked"' : '';
				$featured = $this->document->isFeaturedIn($section) ? 'checked="checked"' : '';

				$section_id = $section->getId();
				$name = View::escape($section->getName());
				echo "
				<tr><td><label for=\"document-sections-$section_id-id\">$name</label></td>
					<td><input name=\"document[sections][$section_id][id]\" id=\"document-sections-$section_id-id\" type=\"checkbox\" value=\"$section_id\" $linked /></td>
					<td><input name=\"document[sections][$section_id][featured]\" id=\"document-sections-$section_id-featured\" type=\"checkbox\" value=\"1\" $featured /></td>
				</tr>
				";
			}
		?>
	</table>
	</fieldset>
</form>
