<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Document $this->document
 * @param string $this->language
 */
?>
<form id="documentForm" method="post" action="<?php echo $_SERVER['PHP_SELF']; ?>">
	<fieldset><legend>Content</legend>
		<table>
		<tr><td><label for="lang">Current Language</label></td>
			<td><select name="lang" id="lang" onchange="FRAMEWORK.processTabbedForm('documentForm','content','next');">
				<?php
					$list = new LanguageList();
					$list->find();
					foreach($list as $language)
					{
						if ($this->language->getCode() == $language->getCode()) { echo "<option value=\"{$language->getCode()}\" selected=\"selected\">{$language->getNative()}</option>"; }
						else { echo "<option value=\"{$language->getCode()}\">{$language->getNative()}</option>"; }
					}
				?>
				</select>
			</td>
		</tr>
		</tr>
		</table>
		<?php include APPLICATION_HOME.'/includes/editors/'.EDITOR.'.inc'; ?>
	</fieldset>

	<fieldset><legend>Next</legend>
		<p>Move on to the next tab.  The document will not be saved to the database until you click the "Save" button.</p>
		<input type="hidden" name="tab" id="tab" value="sections" />
		<input type="hidden" name="action" id="action" value="next" />
		<button type="submit" class="next">Next</button>
		<button type="cancel" class="cancel" onclick="self.close();">Cancel</button>
		<button type="button" class="save" onclick="FRAMEWORK.processTabbedForm('documentForm','content','save');">Save</button>
	</fieldset>
</form>
