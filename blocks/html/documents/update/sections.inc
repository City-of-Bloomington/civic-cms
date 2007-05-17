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
	<fieldset><legend>Sections</legend>
	<table>
		<?php
			foreach ($this->sectionList as $section)
			{
				if ($this->document->hasSection($section)) { $checked="checked=\"checked\""; } else { $checked=""; }
				echo "
				<tr><td><input name=\"document[sections][{$section->getId()}]\" id=\"document-sections-{$section->getId()}\" type=\"checkbox\" value=\"{$section->getId()}\" $checked /></td>
					<td><label for=\"document-sections-{$section->getId()}\">{$section}</label></td></tr>
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
