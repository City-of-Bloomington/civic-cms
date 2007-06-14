<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Document $this->document
 * @param SectionList $this->sectionList
 */
?>
<form id="documentForm" method="post" action="<?php echo $_SERVER['PHP_SELF']; ?>">
	<fieldset><legend class="required">Sections</legend>
	<table>
	<tr><th>Section</th><th>Linked</th><th>Featured</th></tr>
		<?php
			$document_sections = $this->document->getDocumentSections();

			foreach ($this->sectionList as $section)
			{
				$linked = $this->document->hasSection($section) ? 'checked="checked"' : '';
				$featured = $this->document->isFeaturedIn($section) ? 'checked="checked"' : '';

				$section_id = $section->getId();
				echo "
				<tr><td><label for=\"document-sections-$section_id-id\">{$section}</label></td>
					<td><input name=\"document[sections][$section_id][id]\" id=\"document-sections-$section_id-id\" type=\"checkbox\" value=\"$section_id\" $linked /></td>
					<td><input name=\"document[sections][$section_id][featured]\" id=\"document-sections-$section_id-featured\" type=\"checkbox\" value=\"1\" $featured /></td>
				</tr>
				";
			}
		?>
	</table>
	</fieldset>

	<fieldset><legend>Next</legend>
		<p>Move on to the next tab.  The document will not be saved to the database until you click the "Save" button.</p>
		<input type="hidden" name="tab" id="tab" value="attachments" />
		<input type="hidden" name="action" id="action" value="next" />
		<button type="submit" class="next">Next</button>
		<button type="cancel" class="cancel" onclick="self.close();">Cancel</button>
		<button type="button" class="save" onclick="FRAMEWORK.processTabbedForm('documentForm','sections','save');">Save</button>
	</fieldset>
</form>
